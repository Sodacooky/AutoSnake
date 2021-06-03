#include "Pixel.h"

// sdl
static SDL_Window* sg_pWindow;
static SDL_Renderer* sg_pRenderer;
// window size
static SDL_Rect sg_rectWindow;
// pixel(block) size
static int sg_nPixelSize;
// pixel world size
static int sg_nMapWidth, sg_nMapHeight;

void Pixel::Init(int mapWidth, int mapHeight, int pixelSize) {
  // var asssin
  sg_nMapWidth = mapWidth;
  sg_nMapHeight = mapHeight;
  sg_rectWindow.x = SDL_WINDOWPOS_CENTERED;
  sg_rectWindow.y = SDL_WINDOWPOS_CENTERED;
  sg_rectWindow.w = mapWidth * pixelSize;
  sg_rectWindow.h = mapHeight * pixelSize;
  sg_nPixelSize = pixelSize;
  // sdl init
  SDL_Init(SDL_INIT_EVERYTHING);
  sg_pWindow =
      SDL_CreateWindow(u8"AutoSnake", sg_rectWindow.x, sg_rectWindow.y,
                       sg_rectWindow.w, sg_rectWindow.h, SDL_WINDOW_SHOWN);
  sg_pRenderer = SDL_CreateRenderer(
      sg_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // 以我使用这个库多年的经验，在没毛病的机器上根本不会出问题
  // 所以就不写错误处理了
  SDL_RaiseWindow(sg_pWindow);
}

void Pixel::Clear() { SDL_RenderClear(sg_pRenderer); }

void Pixel::Present() { SDL_RenderPresent(sg_pRenderer); }

void Pixel::SetColor(int r, int g, int b) {
  SDL_SetRenderDrawColor(sg_pRenderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void Pixel::Draw(int mapX, int mapY) {
  SDL_Rect tmpRect = {mapX * sg_nPixelSize, mapY * sg_nPixelSize, sg_nPixelSize,
                      sg_nPixelSize};
  SDL_RenderFillRect(sg_pRenderer, &tmpRect);
}

void Pixel::Draw(const MyPoint& pt) { Draw(pt.x, pt.y); }

void Pixel::DrawLine(int x1, int y1, int x2, int y2) {
  SDL_Point from = {x1 * sg_nPixelSize + sg_nPixelSize / 2,
                    y1 * sg_nPixelSize + sg_nPixelSize / 2};
  SDL_Point to = {x2 * sg_nPixelSize + sg_nPixelSize / 2,
                  y2 * sg_nPixelSize + sg_nPixelSize / 2};
  SDL_RenderDrawLine(sg_pRenderer, from.x, from.y, to.x, to.y);
}

void Pixel::DrawLine(const MyPoint& from, const MyPoint& to) {
  DrawLine(from.x, from.y, to.x, to.y);
}

void Pixel::DrawLine(MyLink<MyPoint>& pts) {
  for (int i = 1; i < pts.Size(); i++) {
    DrawLine(pts.GetWhere(i - 1), pts.GetWhere(i));
  }
}