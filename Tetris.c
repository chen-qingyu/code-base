/*
Linux环境下编译运行
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define ROW 19 // 游戏区域的行数
#define COL 12 // 游戏区域的列数
#define NR 4   // 方块数据大小
#define TYPE 7 // 方块类型数

/* 按键枚举 */
enum key
{
    UP,     // 上
    DOWN,   // 下
    LEFT,   // 左
    RIGHT,  // 右
    STOP,   // 停止
    EXIT,   // 退出
    UNKNOW, // 未知
};

/***** 函数声明区域 ******/
void initalGameArea(void);                // 初始化游戏区域
void drawBlock(char bl[NR][NR]);          // 画方块
void cleanBlock(char bl[NR][NR]);         // 清除方块
void turnBlock(char bl[NR][NR]);          // 旋转方块
void gameEnd(void);                       // 结束游戏
void gameStop(void);                      // 暂停游戏
void showGame(void);                      // 显示游戏
void gameSelf(int signo);                 // 游戏自动运行
void checkDeleteLine(void);               // 检查是否满一行
void checkGameOver(char bl[NR][NR]);      // 检查是否游戏结束
int checkMove(char bl[NR][NR], int flag); // 检查方块是否可移动
void setBufferedInput(bool enable);       // 获取输入

/* 全局变量区域 */
static char gameArea[ROW][COL] = {0};     // 游戏区域数据
static int startX = 4, startY = 6;        // 方块出现的起始位置
static int type = 0;                      // 方块当前类型
static int nextType = 0;                  // 方块的下一种类型
static int diret = 0;                     // 方块的方向
char *state = "\033[32m游戏中...\033[0m"; // 游戏运行状态
static unsigned int level = 0;            // 游戏等级
static unsigned int score = 0;            // 游戏分数
static unsigned int maxScore = 0;         // 游戏最高记录
static FILE *fp = NULL;                   // 用于把记录保存到文件

/* 方块数据 */
char bl[TYPE][NR][NR][NR] =
    {
        /* 第一种方块 */
        {
            {
                /* 第一种方向 */
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
        },

        /* 第二种方块 */
        {
            {
                /* 第一种方向 */
                {2, 2, 2, 2},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 2, 0, 0},
                {0, 2, 0, 0},
                {0, 2, 0, 0},
                {0, 2, 0, 0},
            },
            {
                /* 第三种方向 */
                {2, 2, 2, 2},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 2, 0, 0},
                {0, 2, 0, 0},
                {0, 2, 0, 0},
                {0, 2, 0, 0},
            },
        },

        /* 第三种方块 */
        {
            {
                /* 第一种方向 */
                {3, 0, 0, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 3, 3, 0},
                {0, 3, 0, 0},
                {0, 3, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {3, 3, 3, 0},
                {0, 0, 3, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 0, 3, 0},
                {0, 0, 3, 0},
                {0, 3, 3, 0},
                {0, 0, 0, 0},
            },
        },

        /* 第四种方块 */
        {
            {
                /* 第一种方向 */
                {0, 0, 4, 0},
                {4, 4, 4, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 4, 0, 0},
                {0, 4, 0, 0},
                {0, 4, 4, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {0, 4, 4, 4},
                {0, 4, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 4, 4, 0},
                {0, 0, 4, 0},
                {0, 0, 4, 0},
                {0, 0, 0, 0},
            },
        },

        /* 第五种方块 */
        {
            {
                /* 第一种方向 */
                {0, 5, 0, 0},
                {5, 5, 5, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 5, 0, 0},
                {0, 5, 5, 0},
                {0, 5, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {5, 5, 5, 0},
                {0, 5, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 5, 0, 0},
                {5, 5, 0, 0},
                {0, 5, 0, 0},
                {0, 0, 0, 0},
            },
        },

        /* 第六种方块 */
        {
            {
                /* 第一种方向 */
                {6, 6, 0, 0},
                {0, 6, 6, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 0, 6, 0},
                {0, 6, 6, 0},
                {0, 6, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {6, 6, 0, 0},
                {0, 6, 6, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 0, 6, 0},
                {0, 6, 6, 0},
                {0, 6, 0, 0},
                {0, 0, 0, 0},
            },
        },

        /* 第七种方块 */
        {
            {
                /* 第一种方向 */
                {0, 7, 7, 0},
                {7, 7, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第二种方向 */
                {0, 7, 0, 0},
                {0, 7, 7, 0},
                {0, 0, 7, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第三种方向 */
                {0, 0, 7, 7},
                {0, 7, 7, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                /* 第四种方向 */
                {0, 7, 0, 0},
                {0, 7, 7, 0},
                {0, 0, 7, 0},
                {0, 0, 0, 0},
            },
        },
};

/*
 * 主函数：控制全局流程
 */
int main(void)
{
    /*
     * 设置闹钟：
     * 当前时间间隔为0.7秒，下一次时间间隔为0.7秒
     */
    struct itimerval timer = {{0, 700000}, {0, 700000}};
    setitimer(ITIMER_REAL, &timer, NULL);

    /* 初始化游戏区域 */
    initalGameArea();

    /* 设置游戏信号 */
    signal(SIGALRM, gameSelf);

    /* 初始化方块类型 */
    srand(time(NULL));
    type = rand() % 7;
    nextType = rand() % 7;

    /* 读取文件的最高记录 */
    fp = fopen("./record", "r+");
    if (NULL == fp)
    {
        /*
         * 文件不存在则创建并打开
         * "w"方式打开会自动创建不存在的文
         */
        fp = fopen("./record", "w");
    }
    fscanf(fp, "%u", &maxScore);

    /* 用户操作 */
    char c;
    int key;
    setBufferedInput(false);
    while (1)
    {
        c = getchar();
        switch (c)
        {
            case 'w':
            case 'W':
            case '2':
                key = UP;
                break;
            case 's':
            case 'S':
            case '8':
                key = DOWN;
                break;
            case 'a':
            case 'A':
            case '4':
                key = LEFT;
                break;
            case 'd':
            case 'D':
            case '6':
                key = RIGHT;
                break;
            case ' ':
                key = STOP;
                break;
            case 'q':
            case 'Q':
                key = EXIT;
                break;
            default:
                key = UNKNOW;
        }

        switch (key)
        {
            case RIGHT:
                checkMove(bl[type][diret], RIGHT);
                break;
            case LEFT:
                checkMove(bl[type][diret], LEFT);
                break;
            case DOWN:
                checkMove(bl[type][diret], DOWN);
                break;
            case UP:
                turnBlock(bl[type][(diret + 1) % 4]);
                break;
            case STOP:
                gameStop();
                break;
            case EXIT:
                gameEnd();
                break;
            case UNKNOW:
                continue;
        }

        /* 画方块 */
        drawBlock(bl[type][diret]);

        /* 显示游戏 */
        showGame();

        /* 清除方块 */
        cleanBlock(bl[type][diret]);
    }

    return 0;
}

void setBufferedInput(bool enable)
{
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if (enable && !enabled)
    {
        // restore the former settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        // set the new state
        enabled = true;
    }
    else if (!enable && enabled)
    {
        // get the terminal settings for standard input
        tcgetattr(STDIN_FILENO, &new);
        // we want to keep the old setting to restore them at the end
        old = new;
        // disable canonical mode (buffered i/o) and local echo
        new.c_lflag &= (~ICANON & ~ECHO);
        // set the new settings immediately
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
        // set the new state
        enabled = false;
    }
}

/*
 * 函数名：initalGameArea
 * 函数功能：初始化游戏区域
 * 参数：无
 * 返回值：无
 */
void initalGameArea(void)
{
    int i;

    /* 屏幕设置 */
    printf("\033[2J");            // 清屏
    system("stty -icanon");       // 关缓冲
    system("stty -echo");         // 关回显
    fprintf(stdout, "\033[?25l"); // 关闭鼠标显示

    /* 初始化行 */
    for (i = 0; i < COL; i++)
    {
        gameArea[0][i] = 8;       // 第0行
        gameArea[5][i] = 8;       // 第5行
        gameArea[ROW - 1][i] = 8; // 最后一行
    }

    /* 初始化列 */
    for (i = 0; i < ROW; i++)
    {
        gameArea[i][0] = 8;       // 第0列
        gameArea[i][COL - 1] = 8; // 最后一列
    }

    /* 中间一小列 */
    for (i = 1; i < 5; i++)
    {
        gameArea[i][6] = 8;
    }
}

/*
 * 函数名：gameSelf
 * 函数功能：作为信号函数，闹钟时间一到就自动下落
 * 参数：信号
 * 返回值：无
 */
void gameSelf(int signo)
{
    /* 画方块 */
    drawBlock(bl[type][diret]);

    /* 显示游戏 */
    showGame();

    /* 清除方块 */
    cleanBlock(bl[type][diret]);

    /* 如果方块已经到底 */
    if (!checkMove(bl[type][diret], DOWN))
    {
        /* 检查是否游戏结束 */
        checkGameOver(bl[type][diret]);

        /* 保留已经到底的方块 */
        drawBlock(bl[type][diret]);

        /* 显示游戏结果 */
        showGame();

        /* 到达边界后检查是否可消行 */
        checkDeleteLine();

        /* 重新开始下一个方块 */
        startY = 6;
        startX = 4;
        type = nextType;
        nextType = rand() % 7;
        diret = 0;
    }
}

/*
 * 函数名：checkDeleteLine
 * 函数功能：检查是否可消行
 * 参数：无
 * 返回值：无
 */
void checkDeleteLine(void)
{
    int i, j;
    int x, y;

    /* 检查当前方块的四行区域内 */
    for (i = 3; i >= 0; i--)
    {
        for (j = 1; j < COL - 1; j++)
        {
            /* 检测方块是否满一行 */
            if (gameArea[startY + i][j] == 0)
                break;
            /* 跳过边框区域 */
            else if (gameArea[startY + i][j] == 8)
                break;
        }
        /* 如果满了一行则删除一行 */
        if (j == COL - 1)
        {
            /* 删除满了的一行 */
            for (j = 1; j < COL - 1; j++)
            {
                gameArea[startY + i][j] = 0;
            }

            /* 分数累加 */
            score += 100;

            /* 记录最高分 */
            if (score > maxScore)
            {
                maxScore = score;

                /* 保存最高分 */
                rewind(fp);
                fprintf(fp, "%u\n", maxScore);
            }

            /* 记录级别 */
            if (score % 200 == 0)
            {
                /* 每200分加一级 */
                level++;
            }

            /* 删除后往下移动一行 */
            for (x = 1; x < COL - 1; x++)
            {
                for (y = startY + i; y >= 7; y--)
                {
                    gameArea[y][x] = gameArea[y - 1][x];
                }
            }

            /* 移动的一行需要检测范围加一行 */
            i++;
        }
    }
}

/*
 * 函数名：checkGameOver
 * 函数功能：检查游戏是否结束
 * 参数：待检查方块数据数据
 * 返回值：无
 */
void checkGameOver(char block[NR][NR])
{
    int i;

    for (i = 0; i < NR; i++)
    {
        /* 方块碰到上方边界则游戏结束 */
        if (block[0][i] != 0 && gameArea[startY - 1][startX + i] == 8)
        {
            gameEnd();
        }
    }
}

/*
 * 函数名：turnBlock
 * 函数功能：旋转方块
 * 参数：需要旋转的方块数组数据
 * 返回值：无
 */
void turnBlock(char bl[NR][NR])
{
    int x, y;

    /* 检查是否越界 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
        {
            /* 只能判断到达了边界 */
            if (bl[y][x] != 0 && gameArea[startY + y][startX + x] != 0)
            {
                return;
            }
        }
    }

    /* 两边都没有越界则旋转方块方向 */
    diret = (diret + 1) % 4;
}

/*
 * 函数名：gameStop
 * 函数功能：暂停游戏，等待用户再次启动游戏
 * 参数：无
 * 返回值：无
 */
void gameStop(void)
{
    /* 创建一个暂停的是时钟 */
    struct itimerval stop = {0}, older;

    /* 设置新闹钟并存储旧闹钟 */
    setitimer(ITIMER_REAL, &stop, &older);

    /* 配置暂停后的界面 */
    state = "\033[31m暂停中...\033[0m";
    startY--; // 为了防止按下暂停键后方块下滑一格
    drawBlock(bl[type][diret]);
    showGame();
    cleanBlock(bl[type][diret]);

    /* 等待用户按开始键或退出键 */
    int key;
    while (1)
    {
        key = getchar();

        /* 空格开始 */
        if (key == ' ')
            break;
        /* q 退出 */
        else if (key == 'q' || key == 'Q')
            gameEnd();
    }

    /* 恢复闹钟和游戏 */
    setitimer(ITIMER_REAL, &older, NULL);
    state = "\033[32m游戏中...\033[0m";
}

/*
 * 函数名：checkMove
 * 函数功能：检查方块是否可移动,能移则移
 * 参数：1.方块数组数据 2.方向标志位
 * 返回值：可移动返回1，不能移动返回0
 */
int checkMove(char bl[NR][NR], int flag)
{
    int m, n; // 用于标明可移动方向
    int x, y; // 用于循环

    switch (flag)
    {
        case RIGHT:
            n = 0;
            m = 1;
            break;
        case LEFT:
            n = 0;
            m = -1;
            break;
        case DOWN:
            n = 1;
            m = 0;
            break;
    }

    /* 全局检查 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
        {
            /* 只能判断到达了边界 */
            if (bl[y][x] != 0 && gameArea[startY + y + n][startX + x + m] != 0)
            {
                return 0;
            }
        }
    }

    /* 出来说明没有到达边界 */
    startY += n;
    startX += m;

    return 1;
}

/*
 * 函数名：drawBlock
 * 函数功能：填充方块数据
 * 参数：方块数组数据
 * 返回值：无
 */
void drawBlock(char block[NR][NR])
{
    int x, y;

    /* 画当前方块 */
    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
        {
            if (block[y][x] != 0)
            {
                gameArea[startY + y][startX + x] = block[y][x];
            }
        }
    }

    /* 画提示的下一个方块 */
    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < NR; y++)
        {
            if (bl[nextType][0][x][y] != 0)
                gameArea[3 + x][2 + y] = bl[nextType][0][x][y];
            else
                gameArea[3 + x][2 + y] = 0;
        }
    }
}

/*
 * 函数名：cleanBlock
 * 函数功能：清除方块数据
 * 参数：方块数组数据
 * 返回值：无
 */
void cleanBlock(char bl[NR][NR])
{
    int x, y;

    for (y = 0; y < NR; y++)
    {
        for (x = 0; x < NR; x++)
        {
            if (bl[y][x] != 0)
            {
                gameArea[startY + y][startX + x] = 0;
            }
        }
    }
}

/*
 * 函数名：showGame
 * 函数功能：显示游戏
 * 参数：无
 * 返回值：无
 */
void showGame(void)
{
    int i, j;

    /* 定位到第一行第一列 */
    fprintf(stdout, "\033[1;1H");
    fflush(stdout);

    /* 打印所有数据 */
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (gameArea[i][j] == 0) // 空白区域
            {
                fprintf(stdout, "  ");
            }
            else if (gameArea[i][j] == 8) // 边界区域
            {
                fprintf(stdout, "\033[43m  \033[0m");
            }
            else // 方块区域
            {
                fprintf(stdout, "\033[%dm[]\033[0m", gameArea[i][j] + 40);
            }
        }
        fputc('\n', stdout);
    }

    /* 打印提示信息 */
    fprintf(stdout, "\033[2;3H\033[33m【下一个】\033[0m\n");
    fprintf(stdout, "\033[2;15H当前级别:\033[36m%u\033[0m\n", level);
    fprintf(stdout, "\033[3;15H当前分数:\033[32m%u\033[0m\n", score);
    fprintf(stdout, "\033[4;15H最高记录:\033[35m%u\033[0m\n", maxScore);
    fprintf(stdout, "\033[5;15H当前状态:%s\n", state);

    fprintf(stdout, "\033[7;25HW 翻转");
    fprintf(stdout, "\033[8;25HA,D,S 左,右,下");
    fprintf(stdout, "\033[9;25H空格键暂停");
}

/*
 * 函数名：gameEnd
 * 函数功能：处理游戏结束的设置
 * 参数：无
 * 返回值：无
 */
void gameEnd(void)
{
    /* 配置游戏结束后的界面 */
    state = "\033[31m游戏结束!!\033[0m";
    drawBlock(bl[type][diret]);
    showGame();

    /* 恢复终端设置 */
    system("stty icanon");        // 恢复缓冲
    system("stty echo");          // 恢复回显
    fprintf(stdout, "\033[?25h"); // 恢复鼠标显示

    /* 尾部处理 */
    fprintf(stdout, "\033[200;1H"); // 定位光标到最后一行
    fclose(fp);                     // 关闭文件
    exit(0);                        // 退出程序
}
