#pragma once

#include "./vector3.hpp"
class Block {
public:
  Vector3 position;

  Block();
  Block(unsigned int, unsigned int, unsigned int);
  ~Block();
};
