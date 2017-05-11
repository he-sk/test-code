#include <boost/align/aligned_allocator.hpp>
#include <boost/align/is_aligned.hpp>

#include <cstdlib>
#include <iostream>
#include <vector>

namespace ba = boost::alignment;

#ifndef ELEMENTS
#define ELEMENTS 256
#endif

#ifndef ALIGNMENT
#define ALIGNMENT 4096
#endif

void printInfo(const char* description, int* ptr);

int main(int ac, char** av) {
  std::cout << "Elements: " << ELEMENTS << std::endl;
  std::cout << "Alignment: " << ALIGNMENT << std::endl;
  
  std::vector<int> defaultVector(ELEMENTS);
  printInfo("default vector", defaultVector.data());

  std::vector<int, ba::aligned_allocator<int, ALIGNMENT>> alignedVector(ELEMENTS);
  printInfo("aligned vector", alignedVector.data());
  
  return EXIT_SUCCESS;
}

void printInfo(const char* description, int* ptr) {
  std::cout << "Data of " << description << " at = " << ptr << "; offset = " << ((long) ptr) % ALIGNMENT << "; is aligned = " << ba::is_aligned(ptr, ALIGNMENT) << std::endl;
}
  
