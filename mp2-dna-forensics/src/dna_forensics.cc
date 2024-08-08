#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::string input_file = argv[1];
  std::string dna_sequence = argv[2];

  CheckForDNAMatch(input_file, dna_sequence);

  return 0;
}