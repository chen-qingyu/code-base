// Run-length encoding

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_repeat(const unsigned char* src, int size)
{
    return (size >= 3) && (src[0] == src[1]) && (src[1] == src[2]);
}

static int count_repeat(const unsigned char* src, int size)
{
    int count = 1;
    while (count < size && count < 0x7f && src[count] == src[0])
    {
        count++;
    }
    return count;
}

static int count_distinct(const unsigned char* src, int size)
{
    if (size < 3)
    {
        return size;
    }

    int count = 2;
    int current = src[0], next = src[1];
    while (count < size && count < 0x7f && ((current != next) || (next != src[count])))
    {
        current = next;
        next = src[count];
        count++;
    }
    return count;
}

int rle_encode(const unsigned char* src, int src_size, unsigned char* dst, int dst_size)
{
    int encode_size = 0;
    while (src_size > 0)
    {
        if (is_repeat(src, src_size))
        {
            if ((encode_size + 2) > dst_size)
            {
                return -1;
            }
            int count = count_repeat(src, src_size);
            dst[encode_size++] = count | 0x80;
            dst[encode_size++] = *src;
            src += count;
            src_size -= count;
        }
        else
        {
            int count = count_distinct(src, src_size);
            if ((encode_size + count + 1) > dst_size)
            {
                return -1;
            }
            dst[encode_size++] = count;
            for (int i = 0; i < count; i++)
            {
                dst[encode_size++] = *src++;
            }
            src_size -= count;
        }
    }
    return encode_size;
}

int rle_decode(const unsigned char* src, int src_size, unsigned char* dst, int dst_size)
{
    const unsigned char* size = src + src_size;
    int decode_size = 0;
    while (src < size)
    {
        unsigned char code = *src++;
        int count = code & 0x7F;
        if ((decode_size + count) > dst_size)
        {
            return -1;
        }
        if ((code & 0x80) == 0x80) // decode repeat
        {
            for (int i = 0; i < count; i++)
            {
                dst[decode_size++] = *src;
            }
            src++;
        }
        else // decode distinct
        {
            for (int i = 0; i < count; i++)
            {
                dst[decode_size++] = *src++;
            }
        }
    }
    return decode_size;
}

void test()
{
    char* src;
    unsigned char encode_out[32];
    unsigned char decode_out[32];
    int encode_size;
    int decode_size;

    memset(encode_out, 0, 32);
    src = "\xAA\xAA\xBB\xAA\xAA\xCC";
    encode_size = rle_encode((unsigned char*)src, strlen(src), encode_out, 32);
    assert(memcmp(encode_out, "\x06\xAA\xAA\xBB\xAA\xAA\xCC", encode_size) == 0);
    memset(decode_out, 0, 32);
    decode_size = rle_decode(encode_out, encode_size, decode_out, 32);
    assert(memcmp(decode_out, src, decode_size) == 0);

    memset(encode_out, 0, 32);
    src = "\xAA\xAA\xAA\xAA\xAA\xAA";
    encode_size = rle_encode((unsigned char*)src, strlen(src), encode_out, 32);
    assert(memcmp(encode_out, "\x86\xAA", encode_size) == 0);
    memset(decode_out, 0, 32);
    decode_size = rle_decode(encode_out, encode_size, decode_out, 32);
    assert(memcmp(decode_out, src, decode_size) == 0);
}

enum
{
    Encode,
    Decode,
};

void encode_or_decode(const char* filename, int mode)
{
    // read src file
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "open src file failed.");
        exit(1);
    }

    // alloc buffer
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    unsigned char* buffer = (unsigned char*)malloc(sizeof(char) * file_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "memory error.");
        exit(2);
    }

    // read data to buffer
    size_t result = fread(buffer, 1, file_size, file);
    fclose(file);
    if (result != file_size)
    {
        fprintf(stderr, "reading error.");
        exit(3);
    }

    // encode or decode
    char* out_filename;
    unsigned char* out;
    int out_size;
    if (mode == Encode)
    {
        out_filename = (char*)malloc(sizeof(char) * strlen(filename) + 5); // + ".rle"
        strcpy(out_filename, filename);
        strcat(out_filename, ".rle");

        out = (unsigned char*)malloc(sizeof(char) * file_size * 2);
        out_size = rle_encode(buffer, file_size, out, sizeof(char) * file_size * 2);
    }
    else if (mode == Decode)
    {
        out_filename = (char*)calloc(strlen(filename), sizeof(char));
        strncpy(out_filename, filename, strlen(filename) - 4);

        out = (unsigned char*)malloc(sizeof(char) * file_size * 10);
        out_size = rle_decode(buffer, file_size, out, sizeof(char) * file_size * 10);
    }
    free(buffer);

    // write out file
    file = fopen(out_filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "open out file failed.");
        exit(1);
    }
    result = fwrite(out, 1, out_size, file);
    fclose(file);
    free(out_filename);
    free(out);
    if (result != out_size)
    {
        fprintf(stderr, "write file failed.");
        exit(2);
    }
}

int main(int argc, char const* argv[])
{
    test();

    if (argc != 2)
    {
        fprintf(stderr, "usage: run_length_encoding file[.rle]");
        exit(-1);
    }

    const char* suffix = argv[1] + strlen(argv[1]) - 4;
    if ((strlen(argv[1]) > 4) && (strcmp(suffix, ".rle") == 0))
    {
        encode_or_decode(argv[1], Decode);
    }
    else
    {
        encode_or_decode(argv[1], Encode);
    }

    return 0;
}
