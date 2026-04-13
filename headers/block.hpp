#pragma once

#include "./vector3.hpp"
#include <ostream>
class Block {
public:
  Vector3 position;

  Block();
  Block(unsigned int, unsigned int, unsigned int);
  ~Block();

  friend std::ostream &operator<<(std::ostream &, const Block &);
};
