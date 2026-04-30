#include "../headers/miner.hpp"
#include <algorithm>

Miner::Miner(World *world, size_t x, size_t y)
    : world(world), position(x, y, 0), points(0) {}

unsigned int &Miner::get_points() { return this->points; }
void Miner::add_points(unsigned int val) { this->points += val; }

const Vector3 &Miner::get_position() const { return this->position; }

void Miner::move(const Vector3 &vec) {
  size_t size_x, size_y, size_z;
  this->world->get_size().export_to(size_x, size_y, size_z);
  this->position += vec;

  if (this->position.get_x() < 0) {
    this->position.set_x(0);
  }

  if (this->position.get_x() > size_x - 1) {
    this->position.set_x(size_x - 1);
  }

  if (this->position.get_y() < 0) {
    this->position.set_y(0);
  }

  if (this->position.get_y() > size_y - 1) {
    this->position.set_y(size_y - 1);
  }

  if (this->position.get_z() < 0) {
    this->position.set_z(0);
  }

  if (this->position.get_z() > size_z - 1) {
    this->position.set_z(size_z - 1);
  }

  auto column_opt =
      this->world->get_column(this->position.get_x(), this->position.get_y());

  if (column_opt.has_value()) {
    auto column = column_opt.value();

    std::sort(column.begin(), column.end(), [](const Block &a, const Block &b) {
      return a.get_position().get_z() < b.get_position().get_z();
    });

    this->position.set_z(column.at(0).get().get_position().get_z());
  } else {
    this->position.set_z(9);
  }
}
