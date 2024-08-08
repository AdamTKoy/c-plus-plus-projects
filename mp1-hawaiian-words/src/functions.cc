#include "functions.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Your function definitions should go in this source file.

/*
// vector of pairs mapping vowels to their simple (non-vowel-pair) phonetic
// spelling
std::vector<std::pair<char, std::string>> vowel_pairs = {
    {'a', "ah"}, {'e', "eh"}, {'i', "ee"}, {'o', "oh"}, {'u', "oo"}};
*/

bool CheckInvalid(std::string const& input) {
  std::size_t found = input.find_first_not_of("pPkKhHlLmMnNwWaAeEiIoOuU' ");
  return (found != std::string::npos);
}

bool CheckVowel(unsigned char vowel) {
  // assumes argument already converted to lowercase
  return (vowel == 'a' || vowel == 'e' || vowel == 'i' || vowel == 'o' ||
          vowel == 'u');
}

bool CheckValidVowelPair(unsigned char current, unsigned char next) {
  if ((current == 'a') &&
      (next == 'i' || next == 'e' || next == 'o' || next == 'u')) {
    return true;
  }

  if ((current == 'e') && (next == 'i' || next == 'u')) {
    return true;
  }

  if ((current == 'i') && (next == 'u')) {
    return true;
  }

  if ((current == 'o') && (next == 'i' || next == 'u')) {
    return true;
  }

  if ((current == 'u') && (next == 'i')) {
    return true;
  }

  return false;
}

char WConvert(unsigned char prev) {
  // at this point we already know it's a 'w'
  // for 'w', we need to check the previous character
  if (prev == 'i' || prev == 'e') {
    return 'v';
  }
  return 'w';
}

char ConsonantConvert(std::string const& input, std::size_t index) {
  unsigned char current = tolower(input[index]);
  if (current == 'w') {
    if (index > 0) {
      return WConvert(input[index - 1]);
    }
    return 'w';
  }
  return current;
}

std::string VowelConvert(unsigned char vowel, bool last) {
  std::string vowel_output;
  if (vowel == 'a') {
    vowel_output = "ah";
  } else if (vowel == 'e') {
    vowel_output = "eh";
  } else if (vowel == 'i') {
    vowel_output = "ee";
  } else if (vowel == 'o') {
    vowel_output = "oh";
  } else {
    vowel_output = "oo";
  }
  if (!last) {
    vowel_output += '-';
  }
  return vowel_output;
}

std::string VowelPairConvert(unsigned char current,
                             unsigned char next,
                             bool last) {
  std::string vowel_pair_output;
  if (current == 'a') {
    if (next == 'i' || next == 'e') {
      vowel_pair_output = "eye";
    }
    if (next == 'o' || next == 'u') {
      vowel_pair_output = "ow";
    }
  } else if (current == 'e') {
    if (next == 'i') {
      vowel_pair_output = "ay";
    }
    if (next == 'u') {
      vowel_pair_output = "eh-oo";
    }
  } else if (current == 'i') {
    if (next == 'u') {
      vowel_pair_output = "ew";
    }
  } else if (current == 'o') {
    if (next == 'i') {
      vowel_pair_output = "oy";
    }
    if (next == 'u') {
      vowel_pair_output = "ow";
    }
  } else {
    if (next == 'i') {
      vowel_pair_output = "ooey";
    }
  }

  if (!last) {
    vowel_pair_output += '-';
  }
  return vowel_pair_output;
}

std::string PhoneticConvert(std::string const& input) {
  bool invalid = CheckInvalid(input);

  if (invalid) {
    return (input +
            " contains a character not a part of the Hawaiian language.");
  }

  std::string phonetic_ouput;  // empty string for output

  for (std::size_t i = 0; i < input.size(); i++) {
    if ((input[i] != ' ') && (input[i] != '\'')) {
      unsigned char current = tolower(input[i]);
      bool last = ((i == input.size() - 1) ||
                   (input[i + 1] == ' ' || input[i + 1] == '\'') ||
                   ((CheckValidVowelPair(current, tolower(input[i + 1])) &&
                     ((i + 1) == input.size() - 1))));
      if (CheckVowel(current)) {  // check for vowel
        if ((i < input.size() - 1) && (CheckVowel(tolower(input[i + 1])))) {
          if (CheckValidVowelPair(current, tolower(input[i + 1]))) {
            phonetic_ouput +=
                VowelPairConvert(current, tolower(input[i + 1]), last);
            i++;
          } else {  // not a valid vowel pair
            phonetic_ouput += VowelConvert(current, last);
          }
        } else {  // next character is not a vowel
          phonetic_ouput += VowelConvert(current, last);
        }

      } else {  // not vowel, is a valid consonant
        phonetic_ouput += ConsonantConvert(input, i);
      }

    } else {  // spaces and apostrophes carry over the same
      phonetic_ouput += input[i];
    }
  }
  return phonetic_ouput;
}
