#ifndef __MYLINK_H__
#define __MYLINK_H__

//单链表节点
template <typename T>
struct _MyLink_Node_ {
  _MyLink_Node_* pNextNode = nullptr;
  T content;
};

//单链表
template <typename T>
class MyLink {
 public:
  MyLink();
  //深拷贝
  MyLink(const MyLink& right);
  ~MyLink();

 public:
  //在index位置插入，原index及其后元素后移
  void InsertWhere(const T& to_insert, size_t index);
  //获取index位置元素
  T& GetWhere(size_t index);
  //删除index位置元素，原index后元素前移
  void DeleteWhere(size_t index);
  //查找是否有此元素，返回index
  //-1 on not found
  int Find(const T& to_find);

 public:
  //元素数量
  size_t Size();

 private:
  _MyLink_Node_<T>* m_pHead;
  size_t m_Size;
};

template <typename T>
MyLink<T>::MyLink() {
  m_Size = 0;
  m_pHead = new _MyLink_Node_<T>;
  m_pHead->pNextNode = nullptr;
}

template <typename T>
MyLink<T>::MyLink(const MyLink& right) : MyLink() {
  _MyLink_Node_<T>* r_now = right.m_pHead;
  _MyLink_Node_<T>* now = m_pHead;
  while (r_now->pNextNode != nullptr) {
    now->pNextNode = new _MyLink_Node_<T>;
    now->pNextNode->content = r_now->pNextNode->content;
    now->pNextNode->pNextNode = nullptr;
    now = now->pNextNode;
    r_now = r_now->pNextNode;
  }
}

template <typename T>
MyLink<T>::~MyLink() {
  _MyLink_Node_<T>* now = m_pHead;
  _MyLink_Node_<T>* next = now->pNextNode;
  while (next != nullptr) {
    delete now;
    now = next;
    next = now->pNextNode;
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
  size_t now_index = 0;
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
  size_t now_index = 0;
  while (now_ptr != nullptr && now_index < index) {
    now_ptr = now_ptr->pNextNode;
    now_index++;
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
int MyLink<T>::Find(const T& to_find) {
  int now_index = 0;
  int result_index = -1;
  _MyLink_Node_<T>* now_ptr = m_pHead->pNextNode;
  while (now_ptr != nullptr) {
    if (now_ptr->content == to_find) {
      result_index = now_index;
      break;
    }
    now_ptr = now_ptr->pNextNode;
    now_index++;
  }
  return result_index;
}

template <typename T>
size_t MyLink<T>::Size() {
  return m_Size;
}

#endif  // __MYLINK_H__