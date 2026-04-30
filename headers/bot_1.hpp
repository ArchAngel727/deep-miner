#pragma once

#include "./miner.hpp"

class Bot1 : public Miner {
private:
  Vector3 position;
  World *world;

public:
  Bot1(World *, size_t, size_t);
  ~Bot1() override;

  void mine(const Vector3 &) override;
};
