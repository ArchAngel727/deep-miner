#pragma once

#include "miner.hpp"
#include "player_bot.hpp"
#include "render_engine.hpp"
#include "world.hpp"
#include <string>
#include <vector>
class GameManager {
private:
  bool running;
  World world;
  RenderEngine render_engine;
  PlayerBot player;
  std::vector<Miner> enemies;

  void cmd_tree(std::string);

public:
  GameManager();
  ~GameManager();

  void loop();
};
