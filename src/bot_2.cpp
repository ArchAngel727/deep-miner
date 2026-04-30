#include "../headers/bot_2.hpp"
#include <algorithm>
#include <iostream>

Bot2::Bot2(World *world, size_t x, size_t y)
    : Miner(world, x, y), world(world) {}

Bot2::~Bot2() {}

void Bot2::mine(const Vector3 &vec) {
  auto column_opt = this->world->get_column(vec.get_x(), vec.get_y());

  if (column_opt.has_value()) {
    auto column = column_opt.value();

    std::sort(column.begin(), column.end(), [](const Block &a, const Block &b) {
      return a.get_value() > b.get_value();
    });

    if (column.size() > 2) {
      for (size_t i = 0; i < 3; i++) {
        Vector3 vec = column[i].get().get_position();
        std::cout << vec << '\n';
        this->world->remove_block_at(vec.get_x(), vec.get_y(), vec.get_z() + i);
      }
    } else {
      for (auto b : column) {
        Vector3 vec = b.get().get_position();
        this->world->remove_block_at(vec.get_x(), vec.get_y(), vec.get_z());
      }
    }
  }

  this->move(Vector3(0, 0, -3));
}
