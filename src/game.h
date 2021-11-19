#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "player.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  void Run(Controller &controller,
            Renderer &renderer, std::size_t target_frame_duration);
  void Update();

 private:
  Player player1;
  Player player2;

  SDL_Rect ball;
  SDL_Rect p1;
  SDL_Rect p2;

  std::vector<int> p1_info;

  bool out{false};
  float x_vel{7};
  float y_vel{7};
  int x_dir{1};
  int y_dir{0};

  std::size_t screen_width;
  std::size_t screen_height;

};

#endif