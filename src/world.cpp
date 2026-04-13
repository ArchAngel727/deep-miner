#include "../headers/world.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <vector>

World::World(unsigned int x, unsigned int y, unsigned int z) {
  this->blocks = std::vector<Block>();
  this->blocks.reserve(x * y * z);

  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      for (unsigned int k = 0; k < z; k++) {
        this->blocks.push_back(Block(i, j, k));
      }
    }
  }
}

World::World() : World(5, 5, 10) {}

World::World(unsigned int size) : World(size, size, size) {}

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

void World::print() {
  int i = 0;
  std::for_each(this->blocks.begin(), this->blocks.end(),
                [&i](const Block &block) {
                  std::cout << block << " at " << i << '\n';
                  i++;
                });
}

// bool World::exists_at(const Vector3 &vec) const {
//
// }
