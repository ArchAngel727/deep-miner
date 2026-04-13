#include "../headers/vector3.hpp"

Vector3::Vector3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Vector3::Vector3(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3::~Vector3() {}

const bool Vector3::operator==(const Vector3 &other) const {
  if (this->x == other.x && this->y == other.y && this->z == other.z) {
    return true;
  }

  return false;
}

bool const Vector3::is_at(int x, int y, int z) const {
  if (this->x == x && this->y == y && this->z == z) {
    return true;
  }

  return false;
}

bool const Vector3::is_at(const Vector3 &other) const {
  if (this == &other) {
    return true;
  }

  return false;
}
