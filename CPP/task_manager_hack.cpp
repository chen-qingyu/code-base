// let task manager show CPU usage like a sin curve

#include <windows.h>
#include <cmath>

const int COUNT = 200;
const double PI = 3.1415926;
const int INTERVAL = 100; // busy + idle ms

int main()
{
    SetThreadAffinityMask(GetCurrentThread(), 0x01); // set CPU core #0 run this

    DWORD busy[COUNT];
    DWORD idle[COUNT];

    double radian = 0.0;
    for (int i = 0; i < COUNT; i++)
    {
        // 间隔太小会频繁调度拉高CPU使用率，间隔太大会使其呈锯齿状，经过测试大概总共100ms间隔比较合适
        busy[i] = INTERVAL / 2 + std::sin(PI * radian) * (INTERVAL / 2);
        idle[i] = INTERVAL - busy[i];
        radian += 0.01;
    }

    DWORD start = 0;
    for (int i = 0; true; i = (i + 1) % COUNT)
    {
        start = GetTickCount();

        // busy loop
        while ((GetTickCount() - start) <= busy[i])
        {
        }

        // idle loop
        Sleep(idle[i]);
    }

    return 0;
}
