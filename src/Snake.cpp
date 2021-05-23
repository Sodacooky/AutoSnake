#include "Snake.h"

void Snake::Lengthen() {
  auto the_old_last = m_link_ptBody.GetWhere(m_link_ptBody.Size() - 1);
  m_link_ptBody.InsertWhere(the_old_last, m_link_ptBody.Size());
}

size_t Snake::Length() { return m_link_ptBody.Size(); }

bool Snake::IsOnBody(const SDL_Point& pt) {
  //自己做的链表可没有迭代器可用，那么只能把复杂度上升到n^2了
  //自己做个迭代器那就太“多此一举”了
  for (size_t index = 0; index != m_link_ptBody.Size(); index++) {
    auto tmp_pt = m_link_ptBody.GetWhere(index);
    if (tmp_pt.x == pt.x && tmp_pt.y == pt.y) {
      return true;
    }
  }
  return false;
}

void Snake::ControllerReact() {
  auto tmp = m_Controller->React();
  if (tmp == -1) return;
  if (tmp == 0 && m_nDirection == 2) return;
  if (tmp == 1 && m_nDirection == 3) return;
  if (tmp == 2 && m_nDirection == 0) return;
  if (tmp == 3 && m_nDirection == 1) return;
  m_nDirection = tmp;
}

void Snake::Draw() {
  auto to_draw_pt = m_link_ptBody.GetWhere(0);
  // head
  Pixel::SetColor(128, 128, 255);
  Pixel::Draw(to_draw_pt.x, to_draw_pt.y);
  // body
  Pixel::SetColor(255, 255, 255);
  for (size_t index = 1; index != m_link_ptBody.Size(); index++) {
    to_draw_pt = m_link_ptBody.GetWhere(index);
    Pixel::Draw(to_draw_pt.x, to_draw_pt.y);
  }
}

void Snake::__CreateDefaultBody() {
  // add default point
  m_link_ptBody.InsertWhere({7, 5}, 0);
  m_link_ptBody.InsertWhere({6, 5}, 0);
  m_link_ptBody.InsertWhere({5, 5}, 0);
  // set move direction
  m_nDirection = 3;
}

void Snake::__BodyMoveForward() {
  //身体压入栈
  MyStack<SDL_Point*> stack;
  for (size_t index = 0; index != m_link_ptBody.Size(); index++) {
    stack.Push(&(m_link_ptBody.GetWhere(index)));
  }
  //从尾部开始前移
  while (stack.Size() > 1) {
    auto pToMove = stack.Pop();
    *pToMove = *(stack.Top());
  }
}

void Snake::__HeadMoveForward() {
  auto& head = m_link_ptBody.GetWhere(0);
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

const SDL_Point& Snake::HeadPosition() { return m_link_ptBody.GetWhere(0); }

void Snake::MoveForward() {
  //头后跟随前一格
  __BodyMoveForward();
  //头移动
  __HeadMoveForward();
}

Snake::Snake(ControllerInterface* controller) {
  __CreateDefaultBody();
  m_Controller = controller;
}

Snake::~Snake() {}
