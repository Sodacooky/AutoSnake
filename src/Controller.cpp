#include "Controller.h"

int ManualController::React() {
  int result = -1;
  // key down
  auto keyState = SDL_GetKeyboardState(nullptr);
  if (keyState[SDL_SCANCODE_UP] && !m_arr_bIsKeyHolding[0]) {
    result = 0;
    m_arr_bIsKeyHolding[0] = true;
  } else if (keyState[SDL_SCANCODE_RIGHT] && !m_arr_bIsKeyHolding[1]) {
    result = 1;
    m_arr_bIsKeyHolding[1] = true;
  } else if (keyState[SDL_SCANCODE_DOWN] && !m_arr_bIsKeyHolding[2]) {
    result = 2;
    m_arr_bIsKeyHolding[2] = true;
  } else if (keyState[SDL_SCANCODE_LEFT] && !m_arr_bIsKeyHolding[3]) {
    result = 3;
    m_arr_bIsKeyHolding[3] = true;
  }
  // key up
  if (m_Msg.type == SDL_KEYUP) {
    switch (m_Msg.key.keysym.sym) {
      case SDLK_UP:
        m_arr_bIsKeyHolding[0] = false;
        break;
      case SDLK_RIGHT:
        m_arr_bIsKeyHolding[1] = false;
        break;
      case SDLK_DOWN:
        m_arr_bIsKeyHolding[2] = false;
        break;
      case SDLK_LEFT:
        m_arr_bIsKeyHolding[3] = false;
        break;
    }
  }
  return result;
}
ManualController::ManualController(SDL_Event& msg) : m_Msg(msg) {
  for (int i = 0; i != 4; i++) m_arr_bIsKeyHolding[i] = false;
}
