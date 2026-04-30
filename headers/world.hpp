#pragma once

#include "./block.hpp"
#include "vector3.hpp"
#include <functional>
#include <optional>
#include <vector>
class World {
private:
  Vector3 size;
  unsigned int update_count;
  std::vector<Block> blocks;

public:
  World();
  World(size_t);
  World(size_t, size_t, size_t);
  ~World();

  const Vector3 &get_size() const;

  std::optional<std::reference_wrapper<const Block>>
  get_block_at(size_t, size_t, size_t) const;
  std::optional<std::reference_wrapper<const Block>>
  get_block_at(const Vector3 &) const;

  std::optional<std::vector<std::reference_wrapper<const Block>>>
  get_column(size_t, size_t) const;

  std::optional<std::vector<std::reference_wrapper<Block>>> get_column(size_t,
                                                                       size_t);

  bool exists_at(const Vector3 &) const;

  void remove_block_at(size_t, size_t, size_t);
  void update_world(unsigned int);
};
