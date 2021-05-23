#ifndef __MYLINK_H__
#define __MYLINK_H__

//单链表节点
template <typename T>
class _MyLink_Node_ {
 public:
  _MyLink_Node_* pNextNode = nullptr;
  T content;
};

//单链表
template <typename T>
class MyLink {
 public:
  MyLink();
  ~MyLink();

 public:
  //在index位置插入，原index及其后元素后移
  void InsertWhere(const T& to_insert, size_t index);
  //获取index位置元素
  T& GetWhere(size_t index);
  //删除index位置元素，原index后元素前移
  void DeleteWhere(size_t index);

 public:
  //元素数量
  size_t Size();

 private:
  _MyLink_Node_<T>* m_pHead;
  size_t m_Size;
};

template <typename T>
MyLink<T>::MyLink() {
  m_pHead->pNextNode = nullptr;
}

template <typename T>
MyLink<T>::~MyLink() {
  _MyLink_Node_<T>* now = m_pHead;
  _MyLink_Node_<T>* next = now->pNext;
  while (next != nullptr) {
    delete now;
    now = next;
    next = now->pNext;
  }
}

template <typename T>
void MyLink<T>::InsertWhere(const T& to_insert, size_t index) {
  _MyLink_Node_<T>* now_ptr = m_pHead;
  size_t now_index = 0;
  while (now_ptr != nullptr && now_index < index) {
    now_ptr = now_ptr->pNextNode;
    now_index++;
  }
  if (now_ptr == nullptr) {
    throw "index out of range";
  }
  //当前指向要插入位置的上一个
  _MyLink_Node_<T>* tmp = now_ptr->pNextNode;
  now_ptr->pNextNode = new _MyLink_Node_<T>;
  now_ptr->pNextNode->content = to_insert;
  now_ptr->pNextNode->pNextNode = tmp;
  m_Size++;
}

template <typename T>
T& MyLink<T>::GetWhere(size_t index) {
  _MyLink_Node_<T>* now_ptr = m_pHead->pNextNode;
  size_t now_index;
  while (now_ptr != nullptr && now_index < index) {
    now_ptr = now_ptr->pNextNode;
    now_index++;
  }
  if (now_ptr == nullptr) {
    throw "index out of range";
  }
  return now_ptr->content;
}

template <typename T>
void MyLink<T>::DeleteWhere(size_t index) {
  _MyLink_Node_<T>* now_ptr = m_pHead;
  size_t now_index;
  while (now_ptr != nullptr && now_index < index) {
    now_ptr = now_ptr->pNextNode;
  }
  if (now_ptr == nullptr) {
    throw "index out of range";
  }
  //当前指针是要删除指针的上一个指针
  _MyLink_Node_<T>* tmp = now_ptr->pNextNode->pNextNode;
  delete now_ptr->pNextNode;
  now_ptr->pNextNode = tmp;
  m_Size--;
}

template <typename T>
size_t MyLink<T>::Size() {
  return m_Size;
}

#endif  // __MYLINK_H__