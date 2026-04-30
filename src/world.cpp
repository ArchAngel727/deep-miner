#include "../headers/world.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <random>
#include <utility>
#include <vector>

World::World(size_t x, size_t y, size_t z) {
  this->size = Vector3(x, y, z);
  this->update_count = 0;
  this->blocks = std::vector<Block>();
  this->blocks.reserve(x * y * z);

  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < y; j++) {
      for (size_t k = 0; k < z; k++) {
        this->blocks.push_back(Block(i, j, k));
      }
    }
  }
}

World::World() : World(5, 5, 10) {}

World::World(size_t size) : World(size, size, size) {}

World::~World() {};

const Vector3 &World::get_size() const { return this->size; }

std::optional<std::reference_wrapper<const Block>>
World::get_block_at(size_t x, size_t y, size_t z) const {
  auto it = std::find_if(this->blocks.begin(), this->blocks.end(),
                         [&x, &y, &z](const Block &block) {
                           return block.get_position().is_at(x, y, z);
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
      [&vec](const Block &block) { return block.get_position() == vec; });

  if (it != this->blocks.end()) {
    return std::ref(*it);
  }

  return std::nullopt;
}

void World::remove_block_at(size_t x, size_t y, size_t z) {
  auto it = std::find_if(this->blocks.begin(), this->blocks.end(),
                         [&x, &y, &z](const Block &block) {
                           return block.get_position().is_at(x, y, z);
                         });

  if (it != this->blocks.end()) {
    this->blocks.erase(it);
  }
}

std::optional<std::vector<std::reference_wrapper<const Block>>>
World::get_column(size_t x, size_t y) const {
  std::vector<std::reference_wrapper<const Block>> column;

  for (int i = 0; i < this->get_size().get_z(); i++) {
    for (auto &block : this->blocks) {
      if (block.get_position().is_at(x, y, i)) {
        column.push_back(block);
      }
    }
  }

  if (column.size() != 0) {
    return column;
  }

  return std::nullopt;
}

std::optional<std::vector<std::reference_wrapper<Block>>>
World::get_column(size_t x, size_t y) {
  std::vector<std::reference_wrapper<Block>> column;

  for (int i = 0; i < this->get_size().get_z(); i++) {
    for (auto &block : this->blocks) {
      if (block.get_position().is_at(x, y, i)) {
        column.push_back(block);
      }
    }
  }

  if (column.size() != 0) {
    return column;
  }

  return std::nullopt;
}

void World::update_world(unsigned int point_sum) {
  std::random_device rd;
  std::mt19937 gen(rd());

  if (point_sum > this->update_count * 50) {
    this->update_count += 1;
    for (int x = 0; x + 1 < this->size.get_x(); ++x) {
      for (int y = 0; y + 1 < this->size.get_y(); ++y) {
        auto column_opt = this->get_column(x, y);

        if (column_opt.has_value()) {
          auto column = *column_opt;

          switch (rand() % 3) {
          case 0: {
            for (size_t i = 0; i + 1 < column.size(); ++i) {
              for (size_t j = 0; j + 1 < column.size() - i; ++j) {
                if (column[j + 1].get().get_value() <
                    column[j].get().get_value()) {
                  std::swap(column[j].get(), column[j + 1].get());
                }
              }
            }
            break;
          }
          case 1: {
            for (size_t i = 0; i + 1 < column.size(); ++i) {
              for (size_t j = 0; j + 1 < column.size() - i; ++j) {
                if (column[j + 1].get().get_value() >
                    column[j].get().get_value()) {
                  std::swap(column[j], column[j + 1]);
                }
              }
            }
            break;
          }
          case 2:
            std::shuffle(column.begin(), column.end(), gen);
            break;
          }
        }
      }
    }
  }
}
