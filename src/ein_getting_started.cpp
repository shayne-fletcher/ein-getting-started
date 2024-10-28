#include <iostream>

import ein.simd;

int main() {
  ein::simd<int, 4> x{1, 2, 3, 4};
  ein::simd<int, 4> y{4, 3, 2, 1};

  auto z = x * y;
  for(auto it = z.begin(); it != z.end(); ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
