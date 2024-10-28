#include <iostream>

import ein.simd;

int main() {
  ein::simd<int, 4> hello_simd={1, 2, 3, 4};
  for(auto it = hello_simd.begin(); it != hello_simd.end(); ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
