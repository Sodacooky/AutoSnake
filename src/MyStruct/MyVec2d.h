#ifndef __MYVEC2D_H__
#define __MYVEC2D_H__

#include "MyPoint.h"

// 2d向量，大小不可变
template <typename T>
class MyVec2d {
 public:
  MyVec2d() : MyVec2d(30, 20){};
  MyVec2d(size_t width, size_t height)
      : m_nWidth(width), m_nHeight(height), m_nSize(width * height) {
    m_pMem = new T[m_nWidth * m_nHeight];
  }
  ~MyVec2d() { delete[] m_pMem; }

 public:
  T& GetByPos(const MyPoint& pt) { return GetByPos(pt.x, pt.y); }
  T& GetByPos(int x, int y) {
    if (!IsInRange(x, y)) throw "out of range";
    return GetByIndex(y * m_nWidth + x);
  }
  T& GetByIndex(size_t index) {
    if (index >= m_nSize) throw "out of range";
    return m_pMem[index];
  }

 public:
  bool IsInRange(const MyPoint& pt) { return IsInRange(pt.x, pt.y); }
  bool IsInRange(int x, int y) {
    if (x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight) return false;
    return IsInRange(y * m_nWidth + x);
  }
  bool IsInRange(size_t index) {
    if (index >= m_nSize)
      return false;
    else
      return true;
  }

 public:
  void GetSize(size_t& width, size_t& height) {
    width = m_nWidth;
    height = m_nHeight;
  }
  void GetSize(size_t& length) { length = m_nSize; }

 public:
  void SetAll(const T& to_set) {
    for (int i = 0; i != m_nSize; i++) {
      m_pMem[i] = to_set;
    }
  }

 private:
  size_t m_nWidth, m_nHeight, m_nSize;
  T* m_pMem;
};

#endif  // __MYVEC2D_H__