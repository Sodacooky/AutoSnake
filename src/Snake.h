#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "MyStruct/MyLink.h"
#include "MyStruct/MyPoint.h"
#include "MyStruct/MyStack.h"
#include "Pixel.h"

//贪吃蛇本蛇
//内含单向链表阉割版
class Snake {
 public:
  //创建一条长度为3，向左的的蛇
  Snake();
  ~Snake();

 public:
  //蛇头位置
  const MyPoint& HeadPosition();
  //设置方向
  void SetDirection(int direction);
  //向前移动
  void MoveForward();
  //变长
  void Lengthen();

 private:
  //创建一条初始向左长度为3的蛇
  void __CreateDefaultBody();
  //移动的递归函数
  void __BodyMoveForward();
  //根据方向移动头
  void __HeadMoveForward();

 public:
  //蛇身
  MyLink<MyPoint> link_ptBody;

 private:
  //下一步的方向
  // 0 up, 1 right, ...
  int m_nDirection;
  //上一次移动的方向
  int m_nLastMoveDirection;
};

#endif  // __SNAKE_H__