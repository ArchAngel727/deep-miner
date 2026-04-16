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

  void set_x(int);
  void set_y(int);
  void set_z(int);

  bool is_at(int, int, int) const;

  void export_to(size_t &, size_t &, size_t &) const;

  bool operator==(const Vector3 &) const;
  Vector3 &operator+=(const Vector3 &);

  friend std::ostream &operator<<(std::ostream &, const Vector3 &);
};
