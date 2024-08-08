#include "WordSearchSolver.hpp"

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_{puzzle},
    puzzle_height_{puzzle.size()},
    puzzle_width_{puzzle.at(0).size()} {}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation horiz = FindWord(word, CheckDirection::kHorizontal);
  if (!horiz.word.empty()) {
    return horiz;
  }
  WordLocation vert = FindWord(word, CheckDirection::kVertical);
  if (!vert.word.empty()) {
    return vert;
  }
  WordLocation ldiag = FindWord(word, CheckDirection::kLeftDiag);
  if (!ldiag.word.empty()) {
    return ldiag;
  }
  WordLocation rdiag = FindWord(word, CheckDirection::kRightDiag);
  if (!rdiag.word.empty()) {
    return rdiag;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) return CheckHorizontal(word);
  if (direction == CheckDirection::kVertical) return CheckVertical(word);
  if (direction == CheckDirection::kLeftDiag) return CheckLeftDiag(word);
  if (direction == CheckDirection::kRightDiag) return CheckRightDiag(word);
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckHorizontal(const std::string& word) {
  for (std::size_t row = 0; row < puzzle_height_; row++) {
    std::string row_str(puzzle_.at(row).begin(), puzzle_.at(row).end());
    std::size_t found = row_str.find(word);
    if (found != std::string::npos) {
      std::vector<CharPositions> result_vec;
      for (std::size_t idx = 0; idx < word.size(); idx++) {
        CharPositions current = {word[idx], row, found};
        result_vec.push_back(current);
        found++;
      }
      return WordLocation{word, result_vec};
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckVertical(const std::string& word) {
  for (std::size_t col = 0; col < puzzle_width_; col++) {
    std::string col_str = ConvertColumnToString(col);
    std::size_t found = col_str.find(word);
    if (found != std::string::npos) {
      std::vector<CharPositions> result_vec;
      for (std::size_t idx = 0; idx < word.size(); idx++) {
        CharPositions current = {word[idx], found, col};
        result_vec.push_back(current);
        found++;
      }
      return WordLocation{word, result_vec};
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckLeftDiag(const std::string& word) {
  std::size_t diags_to_check =
      puzzle_height_ + puzzle_width_ - 2 * word.size() + 1;
  if (diags_to_check <= 0) return WordLocation{};

  std::size_t row_idx = 0;
  std::size_t col_idx = word.size() - 1;

  for (std::size_t i = 0; i < diags_to_check; i++) {
    std::string ldiag_str = ConvertLeftDiagToString(row_idx, col_idx);
    std::size_t found = ldiag_str.find(word);
    if (found != std::string::npos) {
      std::vector<CharPositions> result_vec;
      for (std::size_t idx = 0; idx < word.size(); idx++) {
        CharPositions current = {word[idx], row_idx + found, col_idx - found};
        result_vec.push_back(current);
        found++;
      }
      return WordLocation{word, result_vec};
    }
    if (col_idx != puzzle_width_ - 1)
      col_idx++;
    else
      row_idx++;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckRightDiag(const std::string& word) {
  std::size_t diags_to_check =
      puzzle_height_ + puzzle_width_ - 2 * word.size() + 1;
  if (diags_to_check <= 0) return WordLocation{};

  std::size_t row_idx = puzzle_height_ - word.size();
  std::size_t col_idx = 0;

  for (std::size_t i = 0; i < diags_to_check; i++) {
    std::string rdiag_str = ConvertRightDiagToString(row_idx, col_idx);
    std::size_t found = rdiag_str.find(word);
    if (found != std::string::npos) {
      std::vector<CharPositions> result_vec;
      for (std::size_t idx = 0; idx < word.size(); idx++) {
        CharPositions current = {word[idx], row_idx + found, col_idx + found};
        result_vec.push_back(current);
        found++;
      }
      return WordLocation{word, result_vec};
    }
    if (row_idx != 0)
      row_idx--;
    else
      col_idx++;
  }
  return WordLocation{};
}

std::string WordSearchSolver::ConvertColumnToString(std::size_t col_idx) {
  std::string result;
  for (std::size_t i = 0; i < puzzle_height_; i++) {
    result += puzzle_.at(i).at(col_idx);
  }
  return result;
}

std::string WordSearchSolver::ConvertLeftDiagToString(std::size_t row_idx,
                                                      std::size_t col_idx) {
  std::string result;
  bool contin = LocationInBounds(row_idx, col_idx);
  while (contin) {
    result += puzzle_.at(row_idx).at(col_idx);
    row_idx++;
    col_idx--;
    contin = LocationInBounds(row_idx, col_idx);
  }
  return result;
}

std::string WordSearchSolver::ConvertRightDiagToString(std::size_t row_idx,
                                                       std::size_t col_idx) {
  std::string result;
  bool contin = LocationInBounds(row_idx, col_idx);
  while (contin) {
    result += puzzle_.at(row_idx).at(col_idx);
    row_idx++;
    col_idx++;
    contin = LocationInBounds(row_idx, col_idx);
  }
  return result;
}