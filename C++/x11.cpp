// Hello World for X11
// Run on Linux Mint
// sudo apt install libx11-dev
// g++ x11.cpp -lX11 -o x11.exe

#include <X11/Xlib.h>
#include <iostream>
#include <string>

int main()
{
    // 打开连接到X服务器
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        std::cerr << "Error: cannot open the default display." << std::endl;
        exit(1);
    }

    int s = DefaultScreen(display);

    // 创建窗口
    Window window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 300, 200, 1, BlackPixel(display, s), WhitePixel(display, s));

    // 选择事件类型
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

    // 显示窗口
    XMapWindow(display, window);

    // 创建图形上下文
    GC gc = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, s));
    XSetBackground(display, gc, WhitePixel(display, s));

    // 注册窗口关闭事件
    Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    // 主事件循环
    XEvent event;
    bool running = true;
    while (running)
    {
        XNextEvent(display, &event);

        if (event.type == Expose)
        {
            // 在窗口中绘制文本
            std::string txt = "Hello World!";
            XDrawString(display, window, gc, 50, 100, txt.c_str(), txt.size());
        }

        if (event.type == KeyPress)
        {
            // 按下任意键退出
            running = false;
        }

        if (event.type == ClientMessage)
        {
            // 检测窗口关闭事件
            if (event.xclient.data.l[0] == wm_delete_window)
            {
                running = false;
            }
        }
    }

    // 清理资源
    XFreeGC(display, gc);
    XCloseDisplay(display);

    return 0;
}
