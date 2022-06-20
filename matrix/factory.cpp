#include "include/vector.hpp"
#include "include/factory.hpp"

Vector<int> Factory::Build() {
  Vector<int> retval { 2, 4, 6 };
  return retval;
}