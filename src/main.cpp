#include "../headers/game_manager.hpp"
#include <ctime>

int main() {
  std::srand(std::time(nullptr));

  GameManager gm;

  gm.loop();

  return 0;
}
