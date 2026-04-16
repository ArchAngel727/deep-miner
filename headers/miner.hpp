#pragma once

#include "vector3.hpp"
#include "world.hpp"
class Miner {
private:
  Vector3 position;
  World *world;

public:
  Miner(World *, size_t, size_t);
  virtual ~Miner();

  const Vector3 &get_position() const;

  void move(const Vector3 &);

  virtual void mine(const Vector3 &);
};
