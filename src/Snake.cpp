#include "Snake.h"

void Snake::Lengthen() {
  auto the_old_last = link_ptBody.GetWhere(link_ptBody.Size() - 1);
  link_ptBody.InsertWhere(the_old_last, link_ptBody.Size());
}

bool Snake::IsOnBody(const MyPoint& pt) {
  auto find_result = link_ptBody.Find(pt);
  if (find_result > 0) return true;
  return false;
}

void Snake::SetDirection(int direction) {
  if (direction == -1) return;
  if (direction == 0 && m_nLastMoveDirection == 2) return;
  if (direction == 1 && m_nLastMoveDirection == 3) return;
  if (direction == 2 && m_nLastMoveDirection == 0) return;
  if (direction == 3 && m_nLastMoveDirection == 1) return;
  m_nDirection = direction;
}

void Snake::Draw() {
  auto to_draw_pt = link_ptBody.GetWhere(0);
  // head
  Pixel::SetColor(128, 128, 255);
  Pixel::Draw(to_draw_pt.x, to_draw_pt.y);
  // body
  Pixel::SetColor(255, 255, 255);
  for (size_t index = 1; index != link_ptBody.Size(); index++) {
    to_draw_pt = link_ptBody.GetWhere(index);
    Pixel::Draw(to_draw_pt.x, to_draw_pt.y);
  }
}

void Snake::__CreateDefaultBody() {
  // add default point
  link_ptBody.InsertWhere(MyPoint(7, 5), 0);
  link_ptBody.InsertWhere(MyPoint(6, 5), 0);
  link_ptBody.InsertWhere(MyPoint(5, 5), 0);
  // set move direction
  m_nDirection = 3;
  m_nLastMoveDirection = 3;
}

void Snake::__BodyMoveForward() {
  //身体压入栈
  MyStack<MyPoint*> stack;
  for (size_t index = 0; index != link_ptBody.Size(); index++) {
    stack.Push(&(link_ptBody.GetWhere(index)));
  }
  //从尾部开始前移
  while (stack.Size() > 1) {
    auto pToMove = stack.Pop();
    *pToMove = *(stack.Top());
  }
}

void Snake::__HeadMoveForward() {
  auto& head = link_ptBody.GetWhere(0);
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
  m_nLastMoveDirection = m_nDirection;
}

const MyPoint& Snake::HeadPosition() { return link_ptBody.GetWhere(0); }

void Snake::MoveForward() {
  //头后跟随前一格
  __BodyMoveForward();
  //头移动
  __HeadMoveForward();
}

Snake::Snake() { __CreateDefaultBody(); }

Snake::~Snake() {}
