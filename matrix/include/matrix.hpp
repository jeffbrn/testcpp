#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <iomanip>
#include <type_traits>
#include <memory>
#include <initializer_list>
#include "MatrixLibException.hpp"

using namespace std;

namespace MatrixLib {
  template<typename T>
  class Matrix {
  public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(new T[rows*cols] {}) /* Initialize unique pointer to new array initialized to zero */ {
      if (!std::is_arithmetic<T>::value) {
        throw MatrixLibException("Matrix is only for numeric types");
      }
      if (rows == 0 || cols == 0) {
        throw MatrixLibException("Rows and cols must be > 0");
      }
      this->rows = rows;
      this->cols = cols;
    }
    Matrix(initializer_list<initializer_list<T>> l) : rows(l.size()), cols(0), data(nullptr) {
      size_t row = 0, col = 0;
      for(auto r : l) {
        if (this->cols == 0) {
          this->cols = r.size();
          this->data.reset(new T[this->rows * this->cols] {});
        } else if (r.size() != this->cols) {
          throw MatrixLibException("Invalid # of colums");
        }
        col = 0;
        for(auto c : r) {
          this->data[(row * this->cols + col++)] = c;
        }
        row += 1;
      }
    }
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    size_t DimRows() {
      return this->rows;
    }

    size_t DimCols() {
      return this->cols;
    }

    // Fetch an element from the matrix
    const T Item(size_t row, size_t col) const {
      if (row > this->rows) throw runtime_error("Invalid row");
      if (col > this->cols) throw runtime_error("Invalid column");
      return this->data[Idx(row, col)];
    }

    // Set an elemnent in the matrix
    void Item(size_t row, size_t col, T val) {
      if (row > this->rows) throw runtime_error("Invalid row");
      if (col > this->cols) throw runtime_error("Invalid column");
      this->data[Idx(row, col)] = val;
    }

    friend ostream& operator<<(ostream& os, const Matrix<T>& m) {
      for(size_t i = 0; i < m.rows; i++) {
        for(size_t j = 0; j < m.cols; j++) {
          if constexpr(std::is_integral_v<T>) { // if the matrix type is integer based
            cout << setw(8) << m.data[i*m.cols + j] << ' ';
          } else { // otherwise is FP 
            cout << setw(8) << setprecision(6) << m.data[i*m.cols + j] << ' ';
          }
        }
        cout << endl;
      } 
      return os;
    }

  private:
    size_t rows, cols;
    unique_ptr<T[]> data;

    // calc index for matrix element
    inline size_t Idx(size_t row, size_t col) {
      return ((row - 1) * this->cols) + (col - 1);
    }
  };
}
#endif
