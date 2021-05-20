#ifndef __MYSTACK_H__
#define __MYSTACK_H__

//链栈
template <typename T>
class MyStack {
 public:
  MyStack() : m_nSize(0), m_pHead(nullptr) { m_pHead = new _Node_<T>; }
  ~MyStack() {
    _Node_<T>* now = m_pHead;
    while (now != nullptr) {
      _Node_<T>* next = now->pNext;
      delete now;
      now = next;
    }
  }

  //访问顶层元素
  //为空时抛出错误
  T& Top() {
    if (m_pHead->pNext == nullptr) {
      throw "empty stack";
    } else {
      return m_pHead->pNext->content;
    }
  }

  //入栈
  void Push(const T& content) {
    _Node_<T>* old_top = m_pHead->pNext;
    m_pHead->pNext = new _Node_<T>;
    m_pHead->pNext->content = content;
    m_pHead->pNext->pNext = old_top;
    m_nSize++;
  }

  //出栈，删除顶层元素
  //为空抛出错误
  void Pop() {
    if (m_pHead->pNext == nullptr) {
      throw "empty stack";
    } else {
      _Node_<T>* old_top = m_pHead->pNext;
      m_pHead->pNext = old_top->pNext;
      delete old_top;
      m_nSize--;
    }
  }

  //大小
  int Size() { return m_nSize; }

 private:
  /*  带头结点的单向链表 */
  template <typename TT>
  class _Node_ {
   public:
    _Node_() : pNext(nullptr) {}
    TT content;
    _Node_* pNext;
  };
  _Node_<T>* m_pHead;

  int m_nSize;
};

#endif  // __MYSTACK_H__