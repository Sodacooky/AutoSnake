﻿#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <SDL2/SDL.h>

//抽象控制器
class ControllerInterface {
 public:
  ControllerInterface();

  //根据因素操作，返回蛇方向
  virtual int React() = 0;

 protected:
};

//手动控制器
class ManualController : public ControllerInterface {
 public:
  // need sdl_event
  ManualController(SDL_Event& msg) : m_Msg(msg){};
  //根据当前键盘状态(或者键盘事件)操作蛇
  virtual int React() override;

 private:
  SDL_Event& m_Msg;
};

//自动控制器
class AutoController : public ControllerInterface {
 public:
  // need map
  AutoController(GameMap& map) : m_Map(map) {}
  //根据地图状态操作蛇
  virtual int React() override;

 private:
  GameMap& m_Map;
};

#endif  // __CONTROLLER_H__