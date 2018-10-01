#include "vector.hh"

#include <algorithm>
#include <cassert>

Vector::Vector(std::size_t size, double value):
size(size),
values(new double[size])
{
    assert(size); // sanity check

    std::fill(values, values + size, value);
}

Vector::Vector(std::initializer_list<double> list):
size(list.size()),
values(new double[size])
{
    assert(size); // sanity check

    std::copy(list.begin(), list.end(), values);
}

Vector::Vector(const Vector& other):
size(other.size),
values(new double[size])
{
    assert(size); // sanity check

    std::copy(other.values, other.values + size, values);
    // copy constructor does a deep copy, so both objects are still valid, and
    // independent.
}

Vector::Vector(Vector&& other):
size(other.size),
values(other.values)
{
    other.values = nullptr;
    // move constructor changes ownership of pointer, leaving the other object
    // in an invalid state.
}

Vector::~Vector()
{
    if (values) delete [] values; // note array delete.
}

double Vector::operator[](std::size_t index) const
{
    assert(index >= 0 && index < size);

    return values[index];
}

double& Vector::operator[](std::size_t index)
{
    assert(index >= 0 && index < size);

    return values[index];
}

Vector Vector::operator+(const Vector& other) const
{
    Vector ret(*this);

    for (std::size_t i = 0; i < ret.size; ++i) {
        ret.values[i] = values[i] + other.values[i];
    }

    return ret;
}

// Note that this is a global namespace function, not a member.
Vector operator*(double left, const Vector& right)
{
    Vector ret(right);

    for (std::size_t i = 0; i < ret.size; ++i) {
        ret.values[i] *= left;
    }

    return ret;
}

std::ostream& operator<<(std::ostream& left, const Vector& right)
{
    left << '[';
    for (std::size_t i = 0; i < right.size; ++i) {
        if (i) {
            left << ", ";
        }
        left << right[i];
    }
    return left << ']';
}
