#include <iostream>
#include <random>

#include "Controller.h"
#include "Pixel.h"
#include "Snake.h"

void FoodGenerate(MyPoint& food, Snake& snake, int mapW, int mapH) {
  std::default_random_engine rand_engine(SDL_GetTicks());
  std::uniform_int_distribution<int> dis_x(1, mapW - 2);
  std::uniform_int_distribution<int> dis_y(1, mapH - 2);
  bool avaliableFood = false;
  while (!avaliableFood) {
    food.x = dis_x(rand_engine);
    food.y = dis_y(rand_engine);
    if (!snake.IsOnBody(food)) {
      avaliableFood = true;
    }
  }
}

// true on ate
bool AteFood(Snake& snake, const MyPoint& food) {
  auto& snake_head = snake.HeadPosition();
  if (snake_head == food) {
    return true;
  }
  return false;
}

bool IsGameOver(Snake& snake, int w, int h) {
  auto& head = snake.HeadPosition();
  // hit wall
  if (head.x < 0 || head.x >= w || head.y < 0 || head.y >= h) {
    return true;
  }
  // hit itself
  if (snake.IsOnBody(head)) {
    return true;
  }
  return false;
}

int main(int, char**) {
  const int mapWidth = 32;
  const int mapHeight = 24;
  Pixel::Init(mapWidth, mapHeight, 24);

  SDL_Event msg;

  // snake component
  auto ac = new AutoController(mapWidth, mapHeight);
  ControllerInterface* controller = ac;
  Snake snake;

  MyPoint food_position;
  food_position = {7, 7};

  while (true) {
    Pixel::Clear();

    SDL_PollEvent(&msg);
    if (msg.type == SDL_QUIT) break;

    snake.MoveForward();
    if (AteFood(snake, food_position)) {
      snake.Lengthen();
      FoodGenerate(food_position, snake, mapWidth, mapHeight);
    }

    ac->ResetMap();
    ac->MapFillSnake(snake.link_ptBody);
    ac->MapFillFood(food_position);
    snake.SetDirection(controller->React());

    if (IsGameOver(snake, mapWidth, mapHeight)) {
      break;
    }

    Pixel::SetColor(0, 255, 0);
    Pixel::Draw(food_position.x, food_position.y);

    snake.Draw();

    Pixel::SetColor(255, 0, 0);
    ac->DrawPath();

    Pixel::SetColor();
    Pixel::Present();

    SDL_Delay(32);
  }
  return 0;
}
