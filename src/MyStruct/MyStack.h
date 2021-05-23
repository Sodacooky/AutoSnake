#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include "MyLink.h"

//链栈
template <typename T>
class MyStack {
 public:
  MyStack() = default;

 public:
  // add to top
  void Push(const T& to_push);
  // return the top then remove it from
  T Pop();
  // get the top
  T& Top();
  // count of element
  size_t Size();

 private:
  MyLink<T> m_Link;
};

template <typename T>
void MyStack<T>::Push(const T& to_push) {
  m_Link.InsertWhere(to_push, 0);
}

template <typename T>
T MyStack<T>::Pop() {
  T tmp = m_Link.GetWhere(0);  // copy
  m_Link.DeleteWhere(0);
  return tmp;
}

template <typename T>
T& MyStack<T>::Top() {
  return m_Link.GetWhere(0);
}

template <typename T>
size_t MyStack<T>::Size() {
  return m_Link.Size();
}

#endif  // __MYSTACK_H__