#include "../headers/block.hpp"

Block::Block() { this->position = Vector3(); }

Block::Block(unsigned int x, unsigned int y, unsigned int z) {
  this->position = Vector3(x, y, z);
}

Vector3::~Vector3() {};
