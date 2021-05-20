#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "Controller.h"
#include "MyStruct/MyStack.h"
#include "MyStruct/MyVec2d.h"
#include "SDL2/SDL.h"
#include "Snake.h"

//游戏逻辑（导演类
//包括蛇、地图、控制器
class Game {
 public:
  Game(size_t width, size_t height, bool manual_mode);

  //将蛇填充进地图
  void FillSnake();

  //生成食物，返回生成的食物位置

  //是否吃到食物
  bool IsAteFood();

 private:
  // where is the food
  SDL_Point m_ptFood;
  // the snake
  Snake m_Snake;
  // snake controller
  ControllerInterface* m_pController;

  //含有蛇、食物信息的网格地图
  // 0 空；1 蛇；2 食物
  MyVec2d<int> m_v2dMap;
};

#endif  // __GAMEMAP_H__