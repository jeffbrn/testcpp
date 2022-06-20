#ifndef __MATRIX_LIB_EXCEPTION_H
#define __MATRIX_LIB_EXCEPTION_H

#include <stdexcept>

namespace MatrixLib {
  class MatrixLibException : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };
}

#endif
