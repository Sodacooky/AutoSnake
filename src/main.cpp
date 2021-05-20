#include <iostream>
#include <random>

#include "Game.h"
#include "MyStruct/MyVec2d.h"
#include "Pixel.h"

int main(int, char**) {
  const int mapWidth = 32;
  const int mapHeight = 16;
  Pixel::Init(mapWidth, mapHeight, 32);

  Snake snake;
  auto last_move_time = SDL_GetTicks();

  SDL_Point food_position;
  std::default_random_engine rand_engine(last_move_time);
  std::uniform_int_distribution<int> dis_x(0, mapWidth - 1);
  std::uniform_int_distribution<int> dis_y(0, mapHeight - 1);
  food_position = {10, 10};

  SDL_Event msg;
  while (snake.Length() <= 6) {
    SDL_PollEvent(&msg);

    if (msg.type == SDL_KEYUP) {
      switch (msg.key.keysym.sym) {
        case SDLK_UP:
          snake.NextDirection(0);
          break;
        case SDLK_RIGHT:
          snake.NextDirection(1);
          break;
        case SDLK_DOWN:
          snake.NextDirection(2);
          break;
        case SDLK_LEFT:
          snake.NextDirection(3);
          break;
        default:
          break;
      }
    }

    auto now_time = SDL_GetTicks();
    if (now_time - last_move_time > 250) {
      snake.MoveForward();
      last_move_time = now_time;

      auto& snake_head = snake.HeadPosition();
      if (snake_head.x == food_position.x && snake_head.y == food_position.y) {
        snake.Lengthen();
        bool avaliableFood = false;
        while (!avaliableFood) {
          food_position.x = dis_x(rand_engine);
          food_position.y = dis_y(rand_engine);
          if (!snake.IsOnBody(food_position)) {
            avaliableFood = true;
          }
        }
      }
    }

    Pixel::Clear();

    Pixel::SetColor(0, 255, 0);
    Pixel::Draw(food_position.x, food_position.y);

    snake.Draw();
    Pixel::SetColor();
    Pixel::Present();
  }
  return 0;
}
