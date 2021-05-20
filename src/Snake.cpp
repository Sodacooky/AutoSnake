#include "Snake.h"

void Snake::Lengthen() {
  //从尾部伸长，效率很低但能用就行
  auto nowPtr = m_pBodyHead;
  // move to tail
  while (nowPtr->pNext != nullptr) {
    nowPtr = nowPtr->pNext;
  }
  // create new
  auto to_add = new _BodyNode_;
  to_add->pNext = nullptr;
  to_add->pt = nowPtr->pt;
  // append
  nowPtr->pNext = to_add;
  m_nBodyLength++;
}

int Snake::Length() { return m_nBodyLength; }

bool Snake::IsOnBody(const SDL_Point& pt) {
  auto nowPtr = m_pBodyHead;
  while (nowPtr->pNext != nullptr) {
    nowPtr = nowPtr->pNext;
    if (nowPtr->pt.x == pt.x && nowPtr->pt.y == pt.y) {
      return true;
    }
  }
  return false;
}

void Snake::Draw() {
  // draw special head
  auto nowPtr = m_pBodyHead->pNext;
  Pixel::SetColor(0, 0, 255);
  Pixel::Draw(nowPtr->pt.x, nowPtr->pt.y);

  // draw normal body
  Pixel::SetColor(255, 255, 255);
  while (nowPtr->pNext != nullptr) {
    nowPtr = nowPtr->pNext;
    Pixel::Draw(nowPtr->pt.x, nowPtr->pt.y);
  }
}

void Snake::__CreateDefaultBody() {
  // 蛇链表此时保证为空
  // init & create link head
  m_nBodyLength = 0;
  m_pBodyHead = new _BodyNode_;
  m_pBodyHead->pt = {-1, -1};
  m_pBodyHead->pNext = nullptr;

  SDL_Point to_add_pt = {5, 5};
  // create snake head
  m_pBodyHead->pNext = new _BodyNode_;
  auto nowPtr = m_pBodyHead->pNext;
  nowPtr->pt = to_add_pt;
  nowPtr->pNext = nullptr;
  // create 2 body blocks
  nowPtr->pNext = new _BodyNode_;
  nowPtr = nowPtr->pNext;
  to_add_pt = {6, 5};
  nowPtr->pt = to_add_pt;
  nowPtr->pNext = nullptr;
  //
  nowPtr->pNext = new _BodyNode_;
  nowPtr = nowPtr->pNext;
  to_add_pt = {7, 5};
  nowPtr->pt = to_add_pt;
  nowPtr->pNext = nullptr;
  // set move direction
  m_nDirection = 3;
}

void Snake::__BodyMoveForward() {
  //身体压入栈
  MyStack<_BodyNode_*> stack;
  auto nowPtr = m_pBodyHead->pNext;
  while (nowPtr != nullptr) {
    stack.Push(nowPtr);
    nowPtr = nowPtr->pNext;
  }
  //从尾部开始前移
  while (stack.Size() > 1) {
    auto to_move = stack.Top();
    stack.Pop();
    to_move->pt = stack.Top()->pt;
  }
}

void Snake::__HeadMoveForward() {
  auto& head = m_pBodyHead->pNext->pt;
  switch (m_nDirection) {
    case 0:  // up
      head.y -= 1;
      break;
    case 1:  // right
      head.x += 1;
      break;
    case 2:  // down
      head.y += 1;
      break;
    case 3:  // left
      head.x -= 1;
      break;
    default:
      throw "error direction";
      break;
  }
}

const SDL_Point& Snake::HeadPosition() { return m_pBodyHead->pNext->pt; }

void Snake::MoveForward() {
  //响应控制器
  m_nDirection = m_Controller->React();
  //头后跟随前一格
  __BodyMoveForward();
  //头移动
  __HeadMoveForward();
}

Snake::Snake(ControllerInterface* controller) {
  m_Controller = controller;
  __CreateDefaultBody();
}

Snake::~Snake() {
  auto now = m_pBodyHead;
  while (now != nullptr) {
    auto next = now->pNext;
    delete now;
    now = next;
  }
}
