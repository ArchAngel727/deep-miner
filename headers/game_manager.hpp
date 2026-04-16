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
  PlayerBot player;
  std::vector<Miner> enemies;
  RenderEngine render_engine;

  void cmd_tree(std::string);

public:
  GameManager();
  ~GameManager();

  void loop();
};
