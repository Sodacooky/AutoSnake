#include "Controller.h"

ManualController::ManualController(SDL_Event& msg) : m_Msg(msg) {
  for (int i = 0; i != 4; i++) m_arr_bIsKeyHolding[i] = false;
}

int ManualController::React() {
  int result = -1;
  // key down
  auto keyState = SDL_GetKeyboardState(nullptr);
  if (keyState[SDL_SCANCODE_UP] && !m_arr_bIsKeyHolding[0]) {
    result = 0;
    m_arr_bIsKeyHolding[0] = true;
  } else if (keyState[SDL_SCANCODE_RIGHT] && !m_arr_bIsKeyHolding[1]) {
    result = 1;
    m_arr_bIsKeyHolding[1] = true;
  } else if (keyState[SDL_SCANCODE_DOWN] && !m_arr_bIsKeyHolding[2]) {
    result = 2;
    m_arr_bIsKeyHolding[2] = true;
  } else if (keyState[SDL_SCANCODE_LEFT] && !m_arr_bIsKeyHolding[3]) {
    result = 3;
    m_arr_bIsKeyHolding[3] = true;
  }
  // key up
  if (m_Msg.type == SDL_KEYUP) {
    switch (m_Msg.key.keysym.sym) {
      case SDLK_UP:
        m_arr_bIsKeyHolding[0] = false;
        break;
      case SDLK_RIGHT:
        m_arr_bIsKeyHolding[1] = false;
        break;
      case SDLK_DOWN:
        m_arr_bIsKeyHolding[2] = false;
        break;
      case SDLK_LEFT:
        m_arr_bIsKeyHolding[3] = false;
        break;
    }
  }
  return result;
}

AutoController::AutoController(int mapWidth, int mapHeight)
    : m_v2_MapBlocks(mapWidth, mapHeight),
      m_ptSnakeHead({-1, -1}),
      m_ptFood({-1, -1}),
      m_ptNextStep({-1, -1}) {
  ResetMap();
}

int AutoController::React() {
  __Spread();
  return __CalcDirection();
}

void AutoController::ResetMap() {
  size_t w, h;
  m_v2_MapBlocks.GetSize(w, h);
  for (int y = 0; y != h; y++) {
    for (int x = 0; x != w; x++) {
      auto& foo = m_v2_MapBlocks.GetByPos(x, y);
      foo.bIsVisited = false;
      foo.bIsPassable = true;
      foo.ptThis = MyPoint(x, y);
      foo.ptFrom = MyPoint(-1, -1);
    }
  }
  m_ptSnakeHead = MyPoint(-1, -1);
  m_ptSnakeEnd = MyPoint(-1, -1);
  m_ptFood = MyPoint(-1, -1);
  m_ptNextStep = MyPoint(-1, -1);
}

void AutoController::MapFillSnake(MyLink<MyPoint>& snake) {
  m_ptSnakeHead = snake.GetWhere(0);
  for (size_t i = 1; i != snake.Size() - 1; i++) {
    auto& block = m_v2_MapBlocks.GetByPos(snake.GetWhere(i));
    block.bIsPassable = false;
    m_ptSnakeEnd = block.ptThis;
  }
}

void AutoController::MapFillFood(const MyPoint& food_position) {
  m_ptFood = food_position;
}

void AutoController::DrawPath() {
  MyPoint nowPt = m_ptSnakeHead;
  while (true) {
    if (nowPt == m_ptFood) break;
    if (nowPt == MyPoint(-1, -1)) break;
    auto& nowblock = m_v2_MapBlocks.GetByPos(nowPt);
    Pixel::DrawLine(nowPt, nowblock.ptFrom);
    nowPt = nowblock.ptFrom;
  }
}

void AutoController::__Spread() {
  MyQueue<_MapBlock_*> que;
  auto ptr = &(m_v2_MapBlocks.GetByPos(m_ptFood));
  ptr->bIsVisited = true;
  que.PushBack(ptr);
  while (que.Size() > 0) {
    auto now = que.Front();
    //判定是否到达头
    if (now->ptThis == m_ptSnakeHead) {
      m_ptNextStep = now->ptFrom;
      break;
    }
    __TryPushPoints(que, now->ptThis);
    que.PopFont();
  }
}

int AutoController::__CalcDirection() {
  if (m_ptNextStep == MyPoint(-1, -1)) {
    return -1;
  }
  if (m_ptNextStep.x - m_ptSnakeHead.x > 0) {
    return 1;
  } else if (m_ptNextStep.x - m_ptSnakeHead.x < 0) {
    return 3;
  }
  if (m_ptNextStep.y - m_ptSnakeHead.y > 0) {
    return 2;
  } else if (m_ptNextStep.y - m_ptSnakeHead.y < 0) {
    return 0;
  }
  return -1;
}

void AutoController::__TryPushPoints(MyQueue<_MapBlock_*>& que,
                                     const MyPoint& pt_from) {
  MyPoint tmpPoint;
  tmpPoint = {pt_from.x - 1, pt_from.y};
  if (__IsAvaliablePoint(tmpPoint)) __PushPointAndSet(que, tmpPoint, pt_from);
  tmpPoint = {pt_from.x + 1, pt_from.y};
  if (__IsAvaliablePoint(tmpPoint)) __PushPointAndSet(que, tmpPoint, pt_from);
  tmpPoint = {pt_from.x, pt_from.y - 1};
  if (__IsAvaliablePoint(tmpPoint)) __PushPointAndSet(que, tmpPoint, pt_from);
  tmpPoint = {pt_from.x, pt_from.y + 1};
  if (__IsAvaliablePoint(tmpPoint)) __PushPointAndSet(que, tmpPoint, pt_from);
}

bool AutoController::__IsAvaliablePoint(const MyPoint& pt) {
  if (m_v2_MapBlocks.IsInRange(pt) == false) {
    // not on map || out of range
    return false;
  }
  if (m_v2_MapBlocks.GetByPos(pt).bIsPassable == false) {
    // cannot run through
    return false;
  }
  if (m_v2_MapBlocks.GetByPos(pt).bIsVisited == true) {
    // already visited
    return false;
  }
  // avaliable
  return true;
}

void AutoController::__PushPointAndSet(MyQueue<_MapBlock_*>& que,
                                       const MyPoint& pt,
                                       const MyPoint& pt_from) {
  auto ptr = &m_v2_MapBlocks.GetByPos(pt);
  ptr->ptFrom = pt_from;
  ptr->bIsVisited = true;
  que.PushBack(ptr);
}

void AutoController::__ResetMapVisitState() {
  size_t w, h;
  m_v2_MapBlocks.GetSize(w, h);
  for (int y = 0; y != h; y++) {
    for (int x = 0; x != w; x++) {
      auto& foo = m_v2_MapBlocks.GetByPos(x, y);
      foo.bIsVisited = false;
      foo.ptFrom = MyPoint(-1, -1);
    }
  }
}
