#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1024 // 缓冲区大小

/* 程序从主函数开始
 * 思路：
 * -> 以读的方式打开源文件
 * -> 以写的方式打开目标文件，如果目标文件不存在则创建
 * -> 读取源文件内容，写入到目标文件上
 * -> 重复循环直到文件读写完成
*/
int main(void)
{
    FILE *fin;  // 源文件
    FILE *fout; // 目标文件
    char *buff; // 缓冲区指针

    int ret; // 用于检查函数是否操作成功

    /* 以读的方式打开源文件 */
    fin = fopen("fcopy.in", "r");
    if (NULL == fin) // 检查打开情况
    {
        return -2;
    }

    /* 以写的方式打开目标文件 */
    fout = fopen("fcopy.out", "w");
    if (NULL == fout) // 检查打开情况
    {
        fclose(fin);
        return -3;
    }

    /* 分配缓冲区内存空间 */
    buff = malloc(BUFFSIZE);
    if (NULL == buff) // 检查分配空间是否成功
    {
        fclose(fout);
        fclose(fin);
        return -3;
    }

    /* 循环读写文件 */
    while (1)
    {
        /* 从源文件中读取内容 */
        ret = fread(buff, 1, BUFFSIZE, fin);

        /* 写入到目标文件中 */
        fwrite(buff, ret, 1, fout);

        if (feof(fin))
        {
            break;
        }
    }

    /* 关闭打开的文件 */
    fclose(fin);
    fclose(fout);

    /* 释放动态分配的内存空间 */
    free(buff);

    return 0;
}
