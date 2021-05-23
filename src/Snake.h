﻿#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SDL2/SDL.h>

#include "Controller.h"
#include "MyStruct/MyLink.h"
#include "MyStruct/MyStack.h"
#include "Pixel.h"

//贪吃蛇本蛇
//内含单向链表阉割版
class Snake {
 public:
  //创建一条长度为3，向左的的蛇
  Snake(ControllerInterface* controller);
  ~Snake();

 public:
  //蛇头位置
  const SDL_Point& HeadPosition();
  //长度
  size_t Length();
  //给定点是否在蛇身上
  bool IsOnBody(const SDL_Point& pt);

 public:
  //根据控制器做出调整
  void ControllerReact();
  //向前移动
  void MoveForward();
  //变长
  void Lengthen();
  //绘制蛇
  //自动设置绘制的颜色
  void Draw();

 private:
  //创建一条初始向左长度为3的蛇
  void __CreateDefaultBody();

  //移动的递归函数
  void __BodyMoveForward();
  //根据方向移动头
  void __HeadMoveForward();

 private:
  //蛇身
  MyLink<SDL_Point> m_link_ptBody;

  //下一步的方向
  // 0 up, 1 right, ...
  int m_nDirection;

  //控制器
  ControllerInterface* m_Controller;
};

#endif  // __SNAKE_H__