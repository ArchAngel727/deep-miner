#pragma once

#include "./miner.hpp"
#include "vector3.hpp"

class PlayerBot : public Miner {
private:
  Vector3 position;
  World *world;

public:
  PlayerBot(World *, size_t, size_t);
  ~PlayerBot() override;

  void mine(const Vector3 &) override;
};
