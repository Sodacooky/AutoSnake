#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Map.h"
#include "MyStruct/MyLink.h"
#include "MyStruct/MyPoint.h"
#include "MyStruct/MyQueue.h"
#include "MyStruct/MyVec2d.h"
#include "Pixel.h"

//抽象控制器
class ControllerInterface {
 public:
  //根据因素操作，返回蛇方向
  // -1 on invalid input
  virtual int React() = 0;
};

//手动控制器
class ManualController : public ControllerInterface {
 private:
  // sdl event
  SDL_Event& m_Msg;
  //方向键按下状态
  bool m_arr_bIsKeyHolding[4];

 public:
  // need sdl_event
  ManualController(SDL_Event& msg);
  //根据当前键盘状态(或者键盘事件)操作蛇
  virtual int React() override;
};

//自动控制器
class AutoController : public ControllerInterface {
 private:
  Map& m_Map;
  MyPoint m_ptCacheNext;

 public:
  // create by new, auto destruct/replace by delete
  MyLink<MyPoint>* m_pPath;

 public:
  //
  AutoController(Map& map);
  ~AutoController();
  //根据地图状态操作蛇，同时绘制路线图
  virtual int React() override;

  //绘制路径
  void DrawPath();

  //寻路部分
 private:
  //通用BST
  // return: nullptr@fail
  MyLink<MyPoint>* __TryBST(const MyPoint& from, const MyPoint& to);

  //从食物不断发散直到发现蛇头（或失败
  //更新MyVec2d<_MapBlock_> m_v2_MapBlocks
  void __Spread();
  //根据下一步位置的相对位置计算蛇的方向
  int __CalcDirection();
};

#endif  // __CONTROLLER_H__