#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

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
  // map state
  struct _MapBlock_ {
    bool bIsPassable;
    bool bIsVisited;
    MyPoint ptThis;
    MyPoint ptFrom;
  };
  MyVec2d<_MapBlock_> m_v2_MapBlocks;

  //蛇头
  MyPoint m_ptSnakeHead;
  //蛇尾
  MyPoint m_ptSnakeEnd;
  //食物
  MyPoint m_ptFood;
  //下一步位置
  MyPoint m_ptNextStep;

 public:
  //
  AutoController(int mapWidth, int mapHeight);
  //根据地图状态操作蛇
  virtual int React() override;

  //清空地图
  void ResetMap();
  //将蛇状态填充入地图
  void MapFillSnake(MyLink<MyPoint>& snake);
  //食物状态填入地图
  void MapFillFood(const MyPoint& food_position);
  //绘制路线
  void DrawPath();

  //寻路部分
 private:
  //从食物不断发散直到发现蛇头（或失败
  //更新MyVec2d<_MapBlock_> m_v2_MapBlocks
  void __Spread();
  //根据下一步位置的相对位置计算蛇的方向
  int __CalcDirection();

 private:
  //尝试将一个点周围的四个点推入队列
  //可以推入队列的条件:
  // 1. 在地图上; 2. 不是障碍; 3. 未被访问过
  void __TryPushPoints(MyQueue<_MapBlock_*>& que, const MyPoint& pt_from);
  //满足要求的点：
  // 1. 在地图上; 2. 不是障碍; 3. 未被访问过
  bool __IsAvaliablePoint(const MyPoint& pt);
  //推入队列并设置为已访问
  void __PushPointAndSet(MyQueue<_MapBlock_*>& que, const MyPoint& pt,
                         const MyPoint& pt_from);
  //清空地图访问状态
  void __ResetMapVisitState();
};

#endif  // __CONTROLLER_H__