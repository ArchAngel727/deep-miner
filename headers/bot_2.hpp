#pragma once

#include "./miner.hpp"

class Bot2 : public Miner {
private:
  Vector3 position;
  World *world;

public:
  Bot2(World *, size_t, size_t);
  ~Bot2() override;

  void mine(const Vector3 &) override;
};
