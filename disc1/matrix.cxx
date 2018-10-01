#include "matrix.hxx"

#include <cassert>

Matrix::Matrix(std::initializer_list<Vector> list)
{
  for (const Vector& vec : list) {
    rows.push_back(vec);
  }
}

Matrix Matrix::matrix_multiply(const Matrix& left, const Matrix& right)
{
  Matrix ret = left;

  return ret; // TODO write this function c:
}

const Vector& Matrix::operator[](std::size_t index) const
{
  assert(index >= 0 && index < rows.size());

  return rows[index];
}

Vector& Matrix::operator[](std::size_t index)
{
  assert(index >= 0 && index < rows.size());

  return rows[index];
}

std::ostream& operator<<(std::ostream& left, const Matrix& right)
{
    left << '[';
    for (std::size_t i = 0; i < right.rows.size(); ++i) {
        if (i) {
            left << ", " << std::endl;
        }
        left << right[i];
    }
    return left << ']';
}