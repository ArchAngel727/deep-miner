#pragma once

#include "render_engine.hpp"
#include "world.hpp"
#include <string>
class GameManager {
private:
  bool running;
  World world;
  RenderEngine render_engine;

  void cmd_tree(std::string);

public:
  GameManager();
  ~GameManager();

  void loop();
};
