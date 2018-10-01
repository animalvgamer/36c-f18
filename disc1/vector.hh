#ifndef __MY_VECTOR_HH__
#define __MY_VECTOR_HH__

#include <cstddef>
#include <initializer_list>
#include <iostream>

// Example class
class Vector {
  protected:
    const size_t size;
    double* values;

  public:
    // standard constructor with default parameter values
    Vector(std::size_t size = 2, double value = 0.0);
    // initializer_list constructor
    Vector(std::initializer_list<double> list);
    // copy constructor
    Vector(const Vector& other);
    // move constructor
    Vector(Vector&& other);

    // destructor (declared virtual to allow inheritance)
    virtual ~Vector();

    // accessors and mutators
    double operator[](size_t index) const;
    double& operator[](size_t index);
    Vector operator+(const Vector& other) const;
    friend Vector operator*(double left, const Vector& right);
    friend std::ostream& operator<<(std::ostream& left, const Vector& right);
};

#endif