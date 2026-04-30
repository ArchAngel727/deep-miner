#include "../headers/bot_1.hpp"

Bot1::Bot1(World *world, size_t x, size_t y)
    : Miner(world, x, y), world(world) {}

Bot1::~Bot1() {}

void Bot1::mine(const Vector3 &vec) {
  for (size_t z = 0; z < 3; z++) {
    auto block = this->world->get_block_at(vec);

    if (block.has_value()) {
      auto b = block.value().get();
      this->add_points(b.get_value());
    }

    this->world->remove_block_at(vec.get_x(), vec.get_y(), vec.get_z() + z);
  }

  this->move(Vector3(0, 0, -3));
}
