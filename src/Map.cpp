#include "Map.h"

Map::Map(size_t width, size_t height) : m_MapBlocks(width, height) {
  for (int y = 0; y != height; y++) {
    for (int x = 0; x != width; x++) {
      auto& b = m_MapBlocks.GetByPos(x, y);
      b.ptMe = {x, y};
      b.ptFrom = {-1, -1};
      b.blockState = _MapBlock_::State::BLANK;
      b.bIsVisited = false;
    }
  }
  ptHead = {-1, -1};
  ptTail = {-1, -1};
}

void Map::Clear() {
  size_t w, h;
  m_MapBlocks.GetSize(w, h);
  for (int y = 0; y != h; y++) {
    for (int x = 0; x != w; x++) {
      auto& b = m_MapBlocks.GetByPos(x, y);
      b.bIsVisited = false;
      b.blockState = _MapBlock_::State::BLANK;
      b.ptFrom = {-1, -1};
    }
  }
  ptHead = {-1, -1};
  ptTail = {-1, -1};
}

void Map::FillSnake(MyLink<MyPoint>& pts) {
  ptHead = pts.GetWhere(0);
  if (m_MapBlocks.IsInRange(ptHead) == false) return;
  m_MapBlocks.GetByPos(pts.GetWhere(0)).blockState = _MapBlock_::State::HEAD;
  for (int i = 1; i != pts.Size(); i++) {
    m_MapBlocks.GetByPos(pts.GetWhere(i)).blockState = _MapBlock_::State::BODY;
  }
}

void Map::FillFood(const MyPoint& pt) {
  m_MapBlocks.GetByPos(pt).blockState = _MapBlock_::State::FOOD;
  ptFood = pt;
}

void Map::FillFood() {
  // make empty list
  MyLink<MyPoint> empty_list;
  size_t w, h;
  m_MapBlocks.GetSize(w, h);
  for (int y = 0; y != h; y++) {
    for (int x = 0; x != w; x++) {
      auto& b = m_MapBlocks.GetByPos(x, y);
      if (b.blockState == _MapBlock_::State::BLANK) {
        empty_list.InsertWhere(b.ptMe, 0);
      }
    }
  }
  // do random
  std::default_random_engine engine(SDL_GetTicks());
  std::uniform_int_distribution<int> dist(0, (int)empty_list.Size() - 1);
  FillFood(empty_list.GetWhere(dist(engine)));
}

MyVec2d<_MapBlock_>& Map::GetInternalMap() { return m_MapBlocks; }

bool Map::IsGameOver() {
  if (__IsSnakeHitWall()) return true;
  if (__IsSnakeHitItself()) return true;
  return false;
}

bool Map::IsAteFood() {
  //判断给定头坐标，对应map中的state是否为food
  if (m_MapBlocks.GetByPos(ptHead).blockState == _MapBlock_::State::FOOD) {
    return true;
  }
  return false;
}

void Map::Draw() {
  size_t w, h;
  m_MapBlocks.GetSize(w, h);
  for (int y = 0; y != h; y++) {
    for (int x = 0; x != w; x++) {
      // set color
      auto& b = m_MapBlocks.GetByPos(x, y);
      switch (b.blockState) {
        case _MapBlock_::State::BLANK:
          // nothing to draw
          Pixel::SetColor(0, 0, 0);
          break;
        case _MapBlock_::State::BODY:
          Pixel::SetColor(255, 255, 255);
          break;
        case _MapBlock_::State::FOOD:
          Pixel::SetColor(0, 255, 0);
          break;
        case _MapBlock_::State::HEAD:
          Pixel::SetColor(0, 0, 255);
          break;
      }  // end set color
      // draw
      Pixel::Draw(x, y);
    }
  }
}

bool Map::__IsSnakeHitWall() {
  //判断头是否在范围外
  size_t w, h;
  m_MapBlocks.GetSize(w, h);
  if (m_MapBlocks.IsInRange(ptHead)) {
    return false;
  } else {
    return true;
  }
}

bool Map::__IsSnakeHitItself() {
  //判断给定头坐标，对应map中的state是否为body
  if (m_MapBlocks.GetByPos(ptHead).blockState == _MapBlock_::State::BODY) {
    return true;
  }
  return false;
}