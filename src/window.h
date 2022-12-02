#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>
#include <iostream>
#include <string>

struct mouseLocation {
    int x;
    int y;
    bool pressed;
};


class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void BlankRectangle(int x, int y, int width, int height, int colour=Red);

  // Draws a string
  void drawString(int x, int y, std::string msg);
  void drawStringBold(int x, int y, std::string msg);
  void drawSym(int x, int y, std::string msg);

  // Mouse Tracking
  mouseLocation getMouseData(int& status);
};

#endif
