#pragma once

#include "./block.hpp"
#include "vector3.hpp"
#include <functional>
#include <optional>
#include <vector>
class World {
private:
  std::vector<Block> blocks;

public:
  World();
  World(unsigned int);
  World(unsigned int, unsigned int, unsigned int);
  ~World();

  std::optional<std::reference_wrapper<const Block>>
  get_block_at(unsigned int, unsigned int, unsigned int) const;
  std::optional<std::reference_wrapper<const Block>>
  get_block_at(const Vector3 &) const;

  bool exists_at(const Vector3 &) const;

  void remove_block_at(unsigned int, unsigned int, unsigned int);
  void print();
};
