#include "../headers/world.hpp"
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

World::World() { this->blocks = std::vector<Block>(); }

World::World(unsigned int size) { this->blocks = std::vector<Block>(size); }

World::World(unsigned int x, unsigned int y, unsigned int z) {
  this->blocks = std::vector<Block>(x * y * z);
}

World::~World() {};

std::optional<std::reference_wrapper<const Block>>
World::get_block_at(unsigned int x, unsigned int y, unsigned int z) const {
  auto it = std::find_if(this->blocks.begin(), this->blocks.end(),
                         [&x, &y, &z](const Block &block) {
                           return block.position.is_at(x, y, z);
                         });

  if (it != this->blocks.end()) {
    return std::ref(*it);
  }

  return std::nullopt;
}

std::optional<std::reference_wrapper<const Block>>
World::get_block_at(const Vector3 &vec) const {
  auto it = std::find_if(
      this->blocks.begin(), this->blocks.end(),
      [&vec](const Block &block) { return block.position.is_at(vec); });

  if (it != this->blocks.end()) {
    return std::ref(*it);
  }

  return std::nullopt;
}
