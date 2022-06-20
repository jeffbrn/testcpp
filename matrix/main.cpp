#include <memory>
#include <iostream>
#include "./include/matrix.hpp"
#include "./include/vector.hpp"
#include "./include/factory.hpp"

using namespace std;
using namespace MatrixLib;

int main() {
  //cout << "Hello world!" << endl;

  auto m = unique_ptr<Matrix<float>>(new Matrix<float>(2, 3));
  m->Item(1, 2, 1.12345f);
  m->Item(2, 3, 12.2468f);
  cout << *m << endl;

  Vector<int> v = {-1, 2, 3};
  v[1] = 1;
  auto x = v[1];
  cout << "First element = " << x << endl;
  cout << v << endl;
  Vector<int> a(v);
  cout << a << endl;
  Vector<int> b(3);
  b = a;
  b += a;
  auto c = v + a + b;
  cout << c << endl;

  cout << "Using factory" << endl;
  auto abc = Factory::Build();
}
