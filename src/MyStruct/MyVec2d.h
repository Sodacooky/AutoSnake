#ifndef __MYVEC2D_H__
#define __MYVEC2D_H__

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

  T& GetByPos(int x, int y) { return GetByIndex(y * m_nWidth + m_nHeight); }
  T& GetByIndex(int index) {
    if (index < 0 || index >= m_nSize) {
      throw "out of range";
    }
    return m_pMem[index];
  }

  bool IsInRange(int x, int y) { return IsInRange(y * m_nWidth + m_nHeight); }
  bool IsInRange(int index) {
    if (index < 0 || index >= m_nSize) {
      return false;
    } else {
      return true;
    }
  }

 private:
  size_t m_nWidth, m_nHeight, m_nSize;
  T* m_pMem;
};

#endif  // __MYVEC2D_H__