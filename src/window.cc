#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

struct mouseLocation {
    int x;
    int y;
    bool pressed;
};


Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XMapRaised(d, w);
  XSetStandardProperties(d, w, "CS246 - Chess++", "CS246 - Chess++", None, NULL, 0, NULL);
  XSelectInput(d, w, ExposureMask | ButtonPressMask | KeyPressMask);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::BlankRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[Red]);
  int thickness = 3;
  XFillRectangle(d, w, gc, x, y, width, thickness);
  XFillRectangle(d, w, gc, x, y+height-thickness, width, thickness);
  XFillRectangle(d, w, gc, x+width-thickness, y, thickness, height);
  XFillRectangle(d, w, gc, x, y, thickness, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawStringBold(int x, int y, string msg) {
  char **missing_charset_list_return;
  int missing_charset_count_return;
  char *def_string_return;
  std::string fontname = "-*-*-demibold-r-*-*-34-240-100-100-*-203-*-*";
  XFontSet setB = XCreateFontSet(d, fontname.c_str(), &missing_charset_list_return, &missing_charset_count_return, &def_string_return);
  Xutf8DrawString(d,w,setB,DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  XFreeFontSet(d, setB);
}

void Xwindow::drawString(int x, int y, string msg) {
  char **missing_charset_list_return;
  int missing_charset_count_return;
  char *def_string_return;
  std::string fontname = "-*-*-*-r-*-*-25-*-100-100-*-203-*-*";
  XFontSet set = XCreateFontSet(d, fontname.c_str(), &missing_charset_list_return, &missing_charset_count_return, &def_string_return);
  Xutf8DrawString(d,w,set,DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  XFreeFontSet(d, set);
}

 // Mouse Tracking
  mouseLocation Xwindow::getMouseData() {
    XEvent event;
    if (XCheckMaskEvent(d, ButtonPress, &event)) {
        //printf(“Clicked at %d,%d\n”, event.xbutton.x, event.xbutton.y);
        return mouseLocation{event.xbutton.x, event.xbutton.y, true};
    } else {
        return mouseLocation{-1, -1, false};
    }
}


