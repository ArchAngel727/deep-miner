#include "../headers/player_bot.hpp"

PlayerBot::PlayerBot(World *world, size_t x, size_t y)
    : Miner(world, x, y), world(world) {}

PlayerBot::~PlayerBot() {}

void PlayerBot::mine(const Vector3 &vec) {
  this->world->remove_block_at(vec.get_x(), vec.get_y(), vec.get_z());
}
