#include "../headers/block.hpp"

Block::Block() : Block(0, 0, 0) {};

Block::Block(unsigned int x, unsigned int y, unsigned int z) {
  this->position = Vector3(x, y, z);

  this->value = rand() % 10;
}

Block::~Block() {}

const Vector3 &Block::get_position() const { return this->position; }

std::ostream &operator<<(std::ostream &stream, const Block &block) {
  stream << "Block at: " << block.position << ' ';
  stream << "With value: " << block.value;

  return stream;
}
