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

int Vector3::get_x() const { return this->x; }
int Vector3::get_y() const { return this->y; }
int Vector3::get_z() const { return this->z; }

void Vector3::export_to(size_t &x, size_t &y, size_t &z) const {
  x = this->x;
  y = this->y;
  z = this->z;
}

bool Vector3::operator==(const Vector3 &other) const {
  if (this->x == other.x && this->y == other.y && this->z == other.z) {
    return true;
  }

  return false;
}

bool Vector3::is_at(int x, int y, int z) const {
  if (this->x == x && this->y == y && this->z == z) {
    return true;
  }

  return false;
}

std::ostream &operator<<(std::ostream &stream, const Vector3 &vec) {
  stream << "<" << vec.get_x() << ", ";
  stream << vec.get_y() << ", ";
  stream << vec.get_z() << ">";

  return stream;
}
