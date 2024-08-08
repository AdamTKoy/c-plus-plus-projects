#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.hpp"

// convert input file to 2d data matrix (vector of vectors of strings)
std::vector<std::vector<std::string>> ExtractInfo(
    const std::string& input_file_name);

// counts maximum consecutive occurences of a single STR within the provided DNA
// sequence
unsigned int CountConsecutiveOccurences(const std::string& str,
                                        const std::string& dna_seq);

// creates vector with all STR counts for given DNA sequence
std::vector<int> STRCounts(const std::vector<std::string>& strs_vector,
                           const std::string& dna_input);

// compares consecutive STR counts against provided people STR counts from input
// datafile
std::string FindMatchingPerson(
    const std::vector<std::vector<std::string>>& people,
    const std::vector<int>& str_counts);

// Function receives file path (string) and DNA sequence (string)
// and will display results to standard output
void CheckForDNAMatch(const std::string& input_file_name,
                      const std::string& dna_seq);

#endif