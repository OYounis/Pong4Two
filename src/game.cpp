#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Game::Game(std::size_t screen_width, std::size_t screen_height)
  :player1(screen_width, screen_height, 0),
   player2(screen_width, screen_height, 1),
   screen_width(screen_width),
   screen_height(screen_height){
    ball.w = 20;
    ball.h = 20;
    p1_info = player1.GetPaddleInfo();
    ball.x = p1_info[0] + p1_info[3];
    ball.y = (screen_height - ball.h)/2;
  }


void Game::Run(Controller &controller, 
                Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player1, player2);
    Update();
    renderer.Render(player1, player2, ball);

    frame_end = SDL_GetTicks();
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(player1.score, player2.score,frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update(){
  ball.x += x_vel*x_dir;
  ball.y += y_vel*y_dir;

  p1 = player1.GetPaddle();
  p2 = player2.GetPaddle();
  /* Top wall:
   * y_dir is -1; x_dir is x; ball.y <= 0;
  */
  if(ball.y <= 0 && y_dir < 0){
      y_dir = 1;
  } 
  /* Bottom wall:
   * y_dir is 1; x_dir is x; ball.y + ball.h >= screen_height;
  */
  if(ball.y + ball.h >= screen_height && y_dir > 0){ 
      y_dir = -1;
  }
  /* Out
   * x_dir is 1; y_dir is y; ball.x + ball.w >= screen_width;
   * x_dir is -1; y_dir is y; ball.x <=0;
  */
  if(x_dir > 0 && ball.x + ball.w >= screen_width){
      out = true;
  }
  if(x_dir < 0 && ball.x <= 0){
      out = true;
  }

  if(SDL_HasIntersection(&ball, &p1)){
    x_dir = 1;
    if(ball.y > (p1.y + (3*p1.h/8)) && ball.y < (p1.y + (4*p1.h/8))){
        y_dir = 0;
    } else{
      if(ball.y < (p1.y + (3*p1.h/8))){y_dir = 1;}
      else if(ball.y > (p1.y + (4*p1.h/8))){y_dir = -1;}
      else{y_dir = 0;}
    }
  }

  if(SDL_HasIntersection(&ball, &p2)){
    x_dir = -1;
    if(ball.y > (p2.y + (3*p2.h/8)) && ball.y < (p2.y + (4*p2.h/8))){
        y_dir = 0;
    } else{
      if(ball.y < (p2.y + (3*p2.h/8))){y_dir = 1;}
      else if(ball.y > (p2.y + (4*p2.h/8))){y_dir = -1;}
      else{y_dir = 0;}
    }
  }

  if(out){
    out = false;
    player1.Reset();
    player2.Reset();
    
    ball.y = (screen_height - ball.h)/2;
    y_dir = 0;
    if(ball.x > 0){ //point for 1
      player1.score++;
      ball.x = p1_info[0] + p1_info[3];
      x_dir = 1;
    } else{ //point for 2
      player2.score++;
      ball.x = screen_width - p1_info[0] - p1_info[3] - ball.w;
      x_dir = -1;  
    }
  }

}