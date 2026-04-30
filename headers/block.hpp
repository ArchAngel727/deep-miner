#pragma once

#include "./vector3.hpp"
#include <ostream>
class Block {
private:
  Vector3 position;
  int value;

public:
  Block();
  Block(unsigned int, unsigned int, unsigned int);
  ~Block();

  const Vector3 &get_position() const;

  int get_value();
  int get_value() const;

  friend std::ostream &operator<<(std::ostream &, const Block &);
};
