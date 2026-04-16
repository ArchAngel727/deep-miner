#pragma once

#include "player_bot.hpp"
#include "world.hpp"

typedef enum {
  X_POSITIVE,
  Y_POSITIVE,
  Z_POSITIVE,
  X_NEGATIVE,
  Y_NEGATIVE,
  Z_NEGATIVE,
} VIEW_AXIS;

class RenderEngine {
private:
  PlayerBot *player;
  World *world;

  void render_block(VIEW_AXIS, std::vector<std::string> &) const;

  void render_block_buffer(std::vector<std::string> &, size_t, size_t, size_t,
                           size_t, bool) const;

public:
  RenderEngine(World *, PlayerBot *);
  ~RenderEngine();

  const std::string render_to_buffer() const;
};
