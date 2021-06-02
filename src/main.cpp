#include <iostream>
#include <random>

#include "Controller.h"
#include "Pixel.h"
#include "Snake.h"

int main(int, char**) {
  const int mapWidth = 128;
  const int mapHeight = 64;
  Pixel::Init(mapWidth, mapHeight, 8);

  Snake snake;

  Map map(mapWidth, mapHeight);
  map.FillFood({7, 7});
  map.FillSnake(snake.link_ptBody);
  map.FillFood(map.ptFood);

  // snake component
  auto ac = new AutoController(map);
  ControllerInterface* controller = ac;

  SDL_Event msg;

  while (true) {
    Pixel::Clear();

    SDL_PollEvent(&msg);
    if (msg.type == SDL_QUIT) break;

    map.Clear();
    map.FillSnake(snake.link_ptBody);
    map.FillFood(map.ptFood);
    if (map.IsGameOver()) {
      break;
    }
    if (map.IsAteFood()) {
      snake.Lengthen();
      map.Clear();
      map.FillSnake(snake.link_ptBody);
      map.FillFood();
    }

    snake.SetDirection(controller->React());
    snake.MoveForward();

    map.Draw();
    ac->DrawPath();

    Pixel::SetColor();
    Pixel::Present();
  }
  return 0;
}
