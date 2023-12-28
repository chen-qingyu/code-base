// Run-length encoding

#include <assert.h>
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

int main(void)
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

    return 0;
}
