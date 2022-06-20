#include <iostream>
#include "vector.hpp"
#include "factory.hpp"

using namespace std;
using namespace MatrixLib;

int main() {
    cout << "Hello, world!" << endl;
    auto v = Factory::Build();
    cout << v << endl;
}
