#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <SDL2/SDL.h>

#include "MyStruct/MyVec2d.h"

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
  //
  AutoController(int mapWidth, int mapHeight)
      : m_v2d_nMapState(mapWidth, mapHeight){};
  //根据地图状态操作蛇
  virtual int React() override;

  //清空地图
  void CleanupMap();

  //将蛇状态填充入地图
  void MapFillSnake();

  //讲食物状态填入地图
  void MapFillFood(const SDL_Point& food_position);

 private:
  // map state
  // 0 blank; 2 snake; 3 food;
  MyVec2d<int> m_v2d_nMapState;
};

#endif  // __CONTROLLER_H__