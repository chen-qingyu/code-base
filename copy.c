#include <stdio.h>
#include <stdlib.h>

// 缓冲区大小
#define BUFFSIZE 1024

int main(int argc, char const* argv[])
{
    // 检查命令行参数个数
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy <src> <dst>\n");
        return EXIT_FAILURE;
    }

    // 以读的方式打开源文件
    FILE* fin = fopen(argv[1], "r");
    if (NULL == fin)
    {
        fprintf(stderr, "ERROR: Can't open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    // 以写的方式打开目标文件
    FILE* fout = fopen(argv[2], "w");
    if (NULL == fout)
    {
        fclose(fin);
        fprintf(stderr, "ERROR: Can't open file '%s'\n", argv[2]);
        return EXIT_FAILURE;
    }

    // 分配缓冲区内存空间
    char* buff = malloc(BUFFSIZE);
    if (NULL == buff)
    {
        fclose(fout);
        fclose(fin);
        return EXIT_FAILURE;
    }

    // 循环读写文件
    while (1)
    {
        // 从源文件中读取内容
        size_t size = fread(buff, 1, BUFFSIZE, fin);

        // 写入到目标文件中
        fwrite(buff, size, 1, fout);

        // 读到源文件结尾则退出
        if (feof(fin))
        {
            break;
        }
    }

    // 关闭打开的文件
    fclose(fin);
    fclose(fout);

    // 释放缓冲区内存空间
    free(buff);

    return EXIT_SUCCESS;
}
