/*
Linux环境下编译运行
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Display *display;
    Window win;

    // Opens connection to X server
    display = XOpenDisplay(NULL);

    // Create a simple window
    win = XCreateSimpleWindow(display,                // our connection to server
                              RootWindow(display, 0), // parent window (none in this example)
                              0, 0,                   // x,y (w.r.t. parent ... ignored here)
                              300, 150,               // width, height
                              0,                      // border width
                              0x000000,               // border color (ignored in this example)
                              0xFFDD00);              // background color (mustard yellow)

    // Set the title of the window
    XStoreName(display, win, "My First X Window");

    // Make it visible
    XMapWindow(display, win);
    XFlush(display);

    // Wait until user presses a key on keyboard
    getchar();

    // Clean up and close the window
    XUnmapWindow(display, win);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}
