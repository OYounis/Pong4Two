#include "player.h"
#include <iostream>

int Player::GetId(){return id;}

std::vector<int> Player::GetPaddleInfo(){
  std::vector<int> info = {paddle.x, paddle.y, paddle.h, paddle.w};
  return info;
}
SDL_Rect Player::GetPaddle(){return paddle;}

void Player::MoveUP(){
  if(paddle.y - inc <= 0) paddle.y = 0;
  else paddle.y -= inc;
  //std::cout << "Player " << id << " up" << "(" << paddle.x << "," << paddle.y << ")" <<std::endl;
}

void Player::MoveDown(){
  if(paddle.y + inc >= 640 - paddle.h) paddle.y = 640 - paddle.h;
  else paddle.y += inc;
  //std::cout << "Player " << id << " down" << "(" << paddle.x << "," << paddle.y << ")" <<std::endl;
}

void Player::Reset(){
  if(id) paddle.x = screen_width - paddle.w - 10;
  else paddle.x = 10;
  paddle.y = (screen_height - paddle.h)/2;
}
