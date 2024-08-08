#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.hpp"

std::vector<std::vector<std::string>> ExtractFileInfo(
    const std::string& input_file_name) {
  std::vector<std::vector<std::string>> data_matrix;
  std::ifstream ifs{input_file_name};
  int count = 0;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> current = utilities::GetSubstrs(line, ',');
    data_matrix.push_back(current);
    count++;
  }
  return data_matrix;
}

unsigned int CountConsecutiveOccurences(const std::string& str,
                                        const std::string& dna_seq) {
  unsigned int max_count = 0;
  unsigned int current_count = 0;
  std::string::size_type pos = 0;
  std::string::size_type prev_start_idx = 0;
  while ((pos = dna_seq.find(str, pos)) != std::string::npos) {
    if ((current_count == 0) || (pos == prev_start_idx)) {
      current_count++;
    } else {
      if (current_count > max_count) {
        max_count = current_count;
      }
      current_count = 1;
    }
    pos += str.length();
    prev_start_idx = pos;
  }
  if (current_count > max_count) {
    max_count = current_count;
  }
  return max_count;
}

std::vector<int> STRCounts(const std::vector<std::string>& strs_vector,
                           const std::string& dna_input) {
  std::vector<int> final_counts;

  for (unsigned int i = 1; i < strs_vector.size(); i++) {
    std::string current_str = strs_vector.at(i);
    unsigned int max_consecutive =
        CountConsecutiveOccurences(current_str, dna_input);
    final_counts.push_back(max_consecutive);
  }
  return final_counts;
}

std::string FindMatchingPerson(
    const std::vector<std::vector<std::string>>& people,
    const std::vector<int>& str_counts) {
  std::vector<std::string> matches;
  std::string output_str;

  for (unsigned int i = 1; i < people.size(); i++) {
    bool match = true;
    for (unsigned int j = 0; j < str_counts.size(); j++) {
      int current = std::stoi(people.at(i).at(j + 1));
      if (current != str_counts.at(j)) match = false;
    }
    if (match) matches.push_back(people.at(i).at(0));
  }

  if (matches.size() != 1)
    output_str = "No match";
  else
    output_str = matches.at(0);

  return output_str;
}

void CheckForDNAMatch(const std::string& input_file_name,
                      const std::string& dna_seq) {
  std::vector<std::vector<std::string>> data_matrix =
      ExtractFileInfo(input_file_name);

  std::vector<int> str_counts = STRCounts(data_matrix.at(0), dna_seq);

  std::string result = FindMatchingPerson(data_matrix, str_counts);

  std::cout << result << std::endl;
}
