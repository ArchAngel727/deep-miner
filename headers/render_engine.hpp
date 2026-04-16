#pragma once

#include "world.hpp"

typedef enum { w3h2, w2h3 } DISPLAY_RATIO;
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
  World *world;

  void render_block(VIEW_AXIS, std::vector<std::string> &) const;

  void render_block_buffer(std::vector<std::string> &, size_t, size_t, size_t,
                           size_t, bool) const;

public:
  RenderEngine(World *);
  ~RenderEngine();

  const std::string render_to_buffer() const;
};
