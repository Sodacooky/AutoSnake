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

AutoController::AutoController(Map& map)
    : m_Map(map), m_pPath(nullptr), m_ptCacheNext(-1, -1) {
  //...
}

AutoController::~AutoController() {
  if (m_pPath != nullptr) {
    delete m_pPath;
  }
}

int AutoController::React() {
  //生成路径
  if (m_pPath == nullptr) {
    m_pPath = __TryBST(m_Map.ptHead, m_Map.ptFood);
    if (m_pPath == nullptr) return -1;  // still fail
  }
  //存在路径，计算
  int to_ret = -1;
  if (m_pPath->Size() > 0) {
    to_ret = __CalcDirection();
    m_pPath->DeleteWhere(0);
  }
  //走完了，令下次react重新生成路径
  if (m_pPath != nullptr && m_pPath->Size() == 0) {
    delete m_pPath;
    m_pPath = nullptr;
  }
  return to_ret;
}

void AutoController::DrawPath() {
  if (m_pPath != nullptr) {
    Pixel::SetColor(255, 0, 0);
    Pixel::DrawLine(m_Map.ptHead, m_ptCacheNext);
    Pixel::DrawLine(m_pPath->GetWhere(0), m_ptCacheNext);
    Pixel::DrawLine(*m_pPath);
  }
}

MyLink<MyPoint>* AutoController::__TryBST(const MyPoint& from,
                                          const MyPoint& to) {
  auto& blocks = m_Map.GetInternalMap();

  // spread
  MyQueue<MyPoint> que_pt;
  // check if push able
  auto _TryPush = [&](const MyPoint& pt, const MyPoint& from) {
    if (blocks.IsInRange(pt) == false) return;
    auto& block = blocks.GetByPos(pt);
    if (block.bIsVisited == true) return;
    if (block.blockState == _MapBlock_::State::BODY) return;
    block.bIsVisited = true;
    block.ptFrom = from;
    que_pt.PushBack(pt);
  };
  // do spread
  blocks.GetByPos(from).bIsVisited = true;
  que_pt.PushBack(from);
  MyPoint now_pt;
  while (que_pt.Size() > 0) {
    now_pt = que_pt.Front();
    // check stop
    if (now_pt == to) break;

    // try push 4 direction
    _TryPush({now_pt.x - 1, now_pt.y}, now_pt);
    _TryPush({now_pt.x + 1, now_pt.y}, now_pt);
    _TryPush({now_pt.x, now_pt.y - 1}, now_pt);
    _TryPush({now_pt.x, now_pt.y + 1}, now_pt);
    que_pt.PopFont();
  }
  if (now_pt != to) return nullptr;  // fail

  // go back
  auto path = new MyLink<MyPoint>;
  while (now_pt != from) {
    path->InsertWhere(now_pt, 0);
    now_pt = blocks.GetByPos(now_pt).ptFrom;
  }

  return path;
}

int AutoController::__CalcDirection() {
  m_ptCacheNext = m_pPath->GetWhere(0);
  if (m_ptCacheNext.x - m_Map.ptHead.x > 0) {
    return 1;
  } else if (m_ptCacheNext.x - m_Map.ptHead.x < 0) {
    return 3;
  }
  if (m_ptCacheNext.y - m_Map.ptHead.y > 0) {
    return 2;
  } else if (m_ptCacheNext.y - m_Map.ptHead.y < 0) {
    return 0;
  }
  throw "error path point";
  return -1;
}