#include <cstdlib>
#include <iostream>
#include <cmath>

#define WORDSIZE 32

unsigned long ipow(unsigned long base, unsigned long exp);

int main(int ac, char** av) {
  if (ac != 4) {
    std::cerr << "Usage: " << av[0] << " [HASH_TABLE_SIZE] [CONSTANT_FACTOR] [KEY]" << std::endl;
    return EXIT_FAILURE;
  }

  unsigned hashtableSize = std::stoi(av[1]);
  unsigned constantFactor = std::stoul(av[2]);
  unsigned key = std::stoi(av[3]);

  unsigned hashtableSizeBits = std::log2(hashtableSize);
  unsigned long modulus = ipow(2, WORDSIZE);
  unsigned long divisor = ipow(2, WORDSIZE - hashtableSizeBits);
  
  auto indexBitshift = ((unsigned) (key * constantFactor)) >> (WORDSIZE - hashtableSizeBits);
  auto indexModuloDivision = ((key * constantFactor) % modulus) / divisor;
  
  std::cout << "Hash table size: " << hashtableSize << " entries (" << hashtableSizeBits << " bits)" << std::endl;
  std::cout << "Word size:       " << WORDSIZE << std::endl;
  std::cout << "Constant factor: " << constantFactor << std::endl;
  std::cout << "Key:             " << key << std::endl;
  std::cout << "Modulus: " << modulus << std::endl;
  std::cout << "Divisor: " << divisor << std::endl;
  std::cout << "Index (with modulo and division): " << indexModuloDivision << std::endl;
  std::cout << "Index (with bit shift):           " << indexBitshift << std::endl;

  return EXIT_SUCCESS;
}

// adapted from: https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
unsigned long ipow(unsigned long base, unsigned long exp)
{
    unsigned long result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}
