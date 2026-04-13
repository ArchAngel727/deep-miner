#pragma once

#include <ostream>
class Vector3 {
private:
  int x, y, z;

public:
  Vector3();
  Vector3(int, int, int);
  ~Vector3();

  int get_x() const;
  int get_y() const;
  int get_z() const;

  bool is_at(int, int, int) const;
  bool is_at(const Vector3 &) const;

  bool operator==(const Vector3 &) const;

  friend std::ostream &operator<<(std::ostream &, const Vector3 &);
};
