#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

// Your function declarations should go in this header file.

// check for invalid characters
bool CheckInvalid(std::string const& input);

bool CheckVowel(unsigned char vowel);
bool CheckValidVowelPair(unsigned char current, unsigned char next);

// convert input string to phonetic translation
std::string PhoneticConvert(std::string const& input);

std::string VowelConvert(unsigned char vowel, bool last);
std::string VowelPairConvert(unsigned char current,
                             unsigned char next,
                             bool last);
char ConsonantConvert(std::string const& input, std::size_t index);
char WConvert(unsigned char prev);

#endif