#ifndef __MYPOINT_H__
#define __MYPOINT_H__

#include <SDL2/SDL.h>

class MyPoint {
 public:
  MyPoint() : MyPoint(-1, -1){};
  MyPoint(int _x, int _y) : x(_x), y(_y){};
  MyPoint(const SDL_Point& pt) : x(pt.x), y(pt.y){};
  bool operator==(const MyPoint& other) const {
    if (this->x == other.x && this->y == other.y) return true;
    return false;
  }

 public:
  int x, y;
};

#endif  // __MYPOINT_H__