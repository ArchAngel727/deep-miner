#pragma once

#include "vector3.hpp"
class Miner {
private:
  Vector3 position;

public:
  Miner();
  Miner(unsigned int, unsigned int);

  const Vector3 &get_position() const;

  void move(Vector3 &);
};
