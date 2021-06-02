#ifndef __MAP_H__
#define __MAP_H__

#include <random>

#include "MyStruct/MyLink.h"
#include "MyStruct/MyPoint.h"
#include "MyStruct/MyVec2d.h"
#include "Pixel.h"

struct _MapBlock_ {
  MyPoint ptMe;
  MyPoint ptFrom;
  // blank: empty
  // barrier: snake body without head
  enum State { BLANK = 0, HEAD = 1, BODY, FOOD } blockState;
  bool bIsVisited;
};

//地图
class Map {
 public:
  Map(size_t width, size_t height);

 public:
  // set all blank,unvisited,no from
  void Clear();
  // return: blocks changed
  //如果蛇头和蛇身已在同一处，则会被蛇身覆盖
  void FillSnake(MyLink<MyPoint>& pts);
  // return: blocks changed
  //如果食物在头处，覆盖蛇头，这意味着要晚于FillSnake()
  void FillFood(const MyPoint& pt);
  // return: blocks changed
  // auto generate
  //尝试避开蛇随机生成食物，这意味着要晚于FillSnake()
  void FillFood();
  // get the internal map
  MyVec2d<_MapBlock_>& GetInternalMap();

  bool IsGameOver();
  bool IsAteFood();

 public:
  // display
  void Draw();

 private:
  // return:
  //  true@ head .x .y out of width height
  bool __IsSnakeHitWall();
  // return:
  //  true@ pts.first .x. y -> state == head
  bool __IsSnakeHitItself();

 public:
  // snapshot
  MyPoint ptHead;
  // snapshot
  MyPoint ptTail;
  // snapshot
  MyPoint ptFood;

 private:
  MyVec2d<_MapBlock_> m_MapBlocks;
};

#endif  // __MAP_H__