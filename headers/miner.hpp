#pragma once

#include "vector3.hpp"
#include "world.hpp"
class Miner {
private:
  Vector3 position;
  World *world;
  unsigned int points;

public:
  Miner(World *, size_t, size_t);
  virtual ~Miner() = default;

  unsigned int &get_points();
  void add_points(unsigned int);

  const Vector3 &get_position() const;

  virtual void move(const Vector3 &);

  virtual void mine(const Vector3 &) = 0;
};
