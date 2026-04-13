#pragma once

class Vector3 {
private:
  int x, y, z;

public:
  Vector3();
  Vector3(int, int, int);
  ~Vector3();

  bool const is_at(int, int, int) const;
  bool const is_at(const Vector3 &) const;

  bool const operator==(const Vector3 &) const;
};
