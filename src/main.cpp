#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  std::cout<<"Launching....\n";
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::cout<<"Creating renders....\n";
  Controller controller;
  std::cout<<"Establishing control....\n";

  Game game(kScreenWidth, kScreenHeight);
  std::cout<<"Game Created....\n";
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  return 0;
}