#include <conio.h>

#include <iostream>
#include <random>

#include "Controller.h"
#include "Pixel.h"
#include "Snake.h"

void ModeSelect(bool& isAuto) {
  printf("**** 选择游戏模式 ****\n");
  printf("\t1.手动\n");
  printf("\t2.自动\n");
  printf("**** 按下数字选择 ****\n");
  printf("手动模式下按方向键操作移动\n");

  char input;
  while (true) {
    input = _getch();
    if (input == '1') {
      isAuto = false;
      break;
    } else if (input == '2') {
      isAuto = true;
      break;
    } else {
    }
  }
}

void AutoGame() {
  printf("观看寻路算法的游戏吧！\n");

  const int mapWidth = 64;
  const int mapHeight = 32;
  Pixel::Init(mapWidth, mapHeight, 16);

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
      printf("寻路算法败了\n");
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
}

void ManualGame() {
  printf("操作蛇进行游戏吧！\n");

  const int mapWidth = 32;
  const int mapHeight = 24;
  Pixel::Init(mapWidth, mapHeight, 24);

  Snake snake;

  Map map(mapWidth, mapHeight);
  map.FillFood({7, 7});
  map.FillSnake(snake.link_ptBody);
  map.FillFood(map.ptFood);

  SDL_Event msg;

  // snake component
  auto mc = new ManualController(msg);
  ControllerInterface* controller = mc;

  auto last_move_time = SDL_GetTicks();

  while (true) {
    Pixel::Clear();

    SDL_PollEvent(&msg);
    if (msg.type == SDL_QUIT) break;
    snake.SetDirection(controller->React());

    map.Clear();
    map.FillSnake(snake.link_ptBody);
    map.FillFood(map.ptFood);
    if (map.IsGameOver()) {
      printf("你失败了，你的分数是:%zd\n", snake.link_ptBody.Size() - 3);
      break;
    }
    if (map.IsAteFood()) {
      snake.Lengthen();
      map.Clear();
      map.FillSnake(snake.link_ptBody);
      map.FillFood();
    }

    if (SDL_GetTicks() - last_move_time > 250) {
      snake.MoveForward();
      last_move_time = SDL_GetTicks();
    }

    map.Draw();

    Pixel::SetColor();
    Pixel::Present();
  }
}

int main(int, char**) {
  bool isAuto = false;
  ModeSelect(isAuto);
  if (isAuto) {
    AutoGame();
  } else {
    ManualGame();
  }
  return 0;
}
