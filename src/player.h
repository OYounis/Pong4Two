#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "SDL.h"

class Player {
 public:
    int score{0};

    Player(int screen_width, int screen_height, int id)
      : screen_width(screen_width),
        screen_height(screen_height),
        id(id) {
            paddle.w = 20;
            paddle.h = 100;
            if(id) paddle.x = screen_width - paddle.w - 10;
            else paddle.x = 10;
            paddle.y = (screen_height - paddle.h)/2;
            inc = 20;
        }
  
  int GetId();
  std::vector<int> GetPaddleInfo();
  SDL_Rect GetPaddle();

  void MoveUP();
  void MoveDown();
  void Reset();

 private:
  SDL_Rect paddle;
  int id;
  int inc;
  
  int screen_width;
  int screen_height;
};

#endif
