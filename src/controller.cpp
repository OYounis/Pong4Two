#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

void Controller::HandleInput(bool &running, Player &player1, Player &player2){
  SDL_Event e;
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&e)){
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN){
      if(e.key.keysym.sym == SDLK_UP) player2.MoveUP();
      if(e.key.keysym.sym == SDLK_DOWN) player2.MoveDown();
      if(e.key.keysym.sym == SDLK_w) player1.MoveUP();
      if(e.key.keysym.sym == SDLK_s) player1.MoveDown();
    }
  }
}
