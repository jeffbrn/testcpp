#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <memory>
#include <initializer_list>
#include <cmath>
#include "MatrixLibException.hpp"

using namespace std;

namespace MatrixLib {
  template<typename T>
  class Vector {
  public:
    Vector(size_t n) : n { n }, data(new T[n] {}) {
      if (!std::is_arithmetic<T>::value) {
        throw MatrixLibException("Vector is only for numeric types");
      }
      if (n == 0) {
        throw MatrixLibException("Rows and cols must be > 0");
      }
    }
    Vector(initializer_list<T> l) : n { l.size() }, data(new T[l.size()] {}) {
      if (!std::is_arithmetic<T>::value) {
        throw MatrixLibException("Vector is only for numeric types");
      }
      size_t i = 0;
      for(auto x : l) {
        this->data[i++] = x;
      }
    }
    Vector(const Vector& other) : n { other.n }, data(new T[other.n] {}) {
      for(size_t i = 0; i < this->n; i++) {
        this->data[i] = other.data[i];
      }
    }
    Vector& operator=(const Vector& other) {
      this->data.reset(new T[other.n] {});
      this->n = other.n;
      for(size_t i = 0; i < this->n; i++) {
        this->data[i] = other.data[i];
      }
      return *this;
    }

    size_t Dimensions() const { return this->n; }

    const T operator[](size_t idx) const {
      if (idx == 0 || idx > this->n) {
        throw MatrixLibException("Invalid idx");
      }
      return this->data[idx-1];
    }

    T& operator[](size_t idx) {
      if (idx == 0 || idx > this->n) {
        throw MatrixLibException("Invalid idx");
      }
      return this->data[idx-1];
    }

    double Length() const {
      double sum = 0;
      for(size_t i = 0; i < this->n; i++) {
        sum += this->data[i] * this->data[i];
      }
      return sqrt(sum);
    }

    T DotProduct(const Vector<T>& rhs) const {
      if (rhs.n != this->n) {
        throw MatrixLibException("Cannot perform a dot product on different sized vectors");
      }
      T result = 0;
      for(size_t i = 0; i < this->n; i++) {
        result += this->data[i] * rhs.data[i];
      }
      return result;
    }

    double Angle(const Vector<T>& rhs) const {
      auto n = this->DotProduct(rhs);
      auto cos = n / (this->Length() * rhs.Length());
      auto angle = acos(cos);
      return angle;
    }

    Vector<T>& operator+=(const Vector<T>& rhs) {
      if (rhs.n != this->n) {
        throw MatrixLibException("Cannot add different sized vectors");
      }
      for(size_t i = 0; i < this->n; i++) {
        this->data[i] += rhs.data[i];
      }
      return *this;
    }

    friend Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs) {
      lhs += rhs;
      return lhs;
    }

    Vector<T>& operator-=(const Vector<T>& rhs) {
      if (rhs.n != this->n) {
        throw MatrixLibException("Cannot subtract different sized vectors");
      }
      for(size_t i = 0; i < this->n; i++) {
        this->data[i] -= rhs.data[i];
      }
      return *this;
    }

    friend Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs) {
      lhs -= rhs;
      return lhs;
    }

    Vector<T>& operator*=(const T rhs) {
      for(size_t i = 0; i < this->n; i++) {
        this->data[i] *= rhs;
      }
      return *this;
    }

    friend Vector<T> operator*(Vector<T> lhs, const T rhs) {
      lhs *= rhs;
      return lhs;
    }

    Vector<T>& operator*=(const Vector<T>& rhs) {
      if ((this->Dimensions() != 3) || (rhs.Dimensions() != 3)) {
        throw MatrixLibException("Cross-product is only for 3d vectors");
      }
      auto i = this->data[1]*rhs.data[2] - this->data[2]*rhs.data[1];
      auto j = this->data[2]*rhs.data[0] - this->data[0]*rhs.data[2];
      auto k = this->data[0]*rhs.data[1] - this->data[1]*rhs.data[0];
      this->data[0] = i;
      this->data[1] = j;
      this->data[2] = k;
      return *this;
    }

    friend Vector<T> operator*(Vector<T> lhs, const Vector<T>& rhs) {
      lhs *= rhs;
      return lhs;
    }

    friend ostream& operator<<(ostream& os, const Vector<T>& v) {
      os << "( ";
      for(size_t i = 0; i < (v.n - 1); i++) {
        os << v.data[i] << ',';
      }
      os << v.data[v.n-1] << " )";
      return os;
    }

    friend bool operator==(const Vector<T> lhs, const Vector<T>& rhs) {
      if (lhs.n != rhs.n) return false;
      for(size_t i = 0; i < lhs.n; i++) {
        if (lhs.data[i] != rhs.data[i]) return false;
      }
      return true;
    }

    friend bool operator!=(const Vector<T> lhs, const Vector<T>& rhs) { return !(lhs == rhs); }

    Vector<double> Normalize() {
      auto len = (double)this->Length();
      Vector<double> retval(this->n);
      for(size_t i = 0; i < this->n; i++) {
        retval[i+1] = this->data[i] / len;;
      }
      return retval;
    }

  private:
    size_t n;
    unique_ptr<T[]> data;
  };
}
#endif
