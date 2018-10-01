#ifndef __MY_MATRIX_HXX__
#define __MY_MATRIX_HXX__

#include "vector.hh"

#include <initializer_list>
#include <iostream>
#include <vector>

class Matrix
{
 protected:
  std::vector<Vector> rows;
 public:
  Matrix(std::initializer_list<Vector> list);

  // Implement this!!!
  static Matrix matrix_multiply(const Matrix& left, const Matrix& right);
  // Implement this!!!

  const Vector& operator[](size_t index) const;
  Vector& operator[](size_t index);

  friend std::ostream& operator<<(std::ostream& left, const Matrix& right);
};

#endif