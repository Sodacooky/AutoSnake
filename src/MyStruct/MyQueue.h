#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include "MyLink.h"

//队列
template <typename T>
class MyQueue {
 public:
  MyQueue() = default;
  //~MyQueue();

 public:
  void PushBack(const T& to_push);
  void PopFont();

 public:
  T& Front();
  T& Back();
  size_t Size();

 private:
  //这个单链表尾插效率很差，那么翻过来用
  MyLink<T> m_Link;
};

template <typename T>
void MyQueue<T>::PushBack(const T& to_push) {
  m_Link.InsertWhere(to_push, 0);
}

template <typename T>
void MyQueue<T>::PopFont() {
  m_Link.DeleteWhere(m_Link.Size() - 1);
}

template <typename T>
T& MyQueue<T>::Front() {
  return m_Link.GetWhere(m_Link.Size() - 1);
}

template <typename T>
T& MyQueue<T>::Back() {
  return m_Link.GetWhere(0);
  // error when empty
}

template <typename T>
size_t MyQueue<T>::Size() {
  return m_Link.Size();
}

#endif  // __MYQUEUE_H__