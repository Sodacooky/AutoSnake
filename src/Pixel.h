#ifndef __PIXEL_H__
#define __PIXEL_H__

#include <SDL2/SDL.h>

#include "MyStruct/MyLink.h"
#include "MyStruct/MyPoint.h"

//像素块绘制封装
class Pixel {
 public:
  //初始化sdl等
  static void Init(int mapWidth, int mapHeight, int pixelSize = 16);
  //清空缓冲区
  static void Clear();
  //绘制缓冲区
  static void Present();
  //设置下一个绘制的块的颜色
  //这也会影响清空屏幕的“覆盖色”
  static void SetColor(int r = 0, int g = 0, int b = 0);
  //绘制一个块到缓冲区
  //坐标为地图坐标
  static void Draw(int mapX, int mapY);
  //绘制一个块到缓冲区
  //坐标为地图坐标
  static void Draw(const MyPoint& pt);
  //画线连接两个地图坐标方块的中心
  static void DrawLine(int x1, int y1, int x2, int y2);
  //画线连接两个地图坐标方块的中心
  static void DrawLine(const MyPoint& from, const MyPoint& to);
  //画线连接点集
  static void DrawLine(MyLink<MyPoint>& pts);
};

#endif  // __PIXEL_H__