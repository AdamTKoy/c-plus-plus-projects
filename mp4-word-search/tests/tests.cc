// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Horizontal Win", "[horiz_win]") {
  std::vector<std::vector<char>> puzzle{{'o', 'o', 'l', 'o', 'o', 'a'},
                                        {'l', 'o', 'l', 'l', 'e', 'h'},
                                        {'l', 'a', 'l', 'l', 'e', 'a'},
                                        {'e', 'e', 'l', 'l', 'e', 'h'},
                                        {'h', 'e', 'l', 'l', 'o', 'h'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("hello");

  REQUIRE(result.word == "hello");
  REQUIRE(result.char_positions.size() == 5);
  REQUIRE(result.char_positions.at(0).character == 'h');
  REQUIRE(result.char_positions.at(0).row == 4);
  REQUIRE(result.char_positions.at(0).col == 0);
  REQUIRE(result.char_positions.at(1).character == 'e');
  REQUIRE(result.char_positions.at(1).row == 4);
  REQUIRE(result.char_positions.at(1).col == 1);
  REQUIRE(result.char_positions.at(2).character == 'l');
  REQUIRE(result.char_positions.at(2).row == 4);
  REQUIRE(result.char_positions.at(2).col == 2);
  REQUIRE(result.char_positions.at(3).character == 'l');
  REQUIRE(result.char_positions.at(3).row == 4);
  REQUIRE(result.char_positions.at(3).col == 3);
  REQUIRE(result.char_positions.at(4).character == 'o');
  REQUIRE(result.char_positions.at(4).row == 4);
  REQUIRE(result.char_positions.at(4).col == 4);

  result = wss.FindWord("hello", CheckDirection::kHorizontal);
  REQUIRE_FALSE(result.word.empty());
  REQUIRE_FALSE(result.char_positions.empty());
  result = wss.FindWord("hello", CheckDirection::kVertical);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("hello", CheckDirection::kLeftDiag);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("hello", CheckDirection::kRightDiag);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("Vertical Win", "[vert_win]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'n', 'i', 'w', 'r'},
                                        {'c', 'i', 'l', 'i', 'm'},
                                        {'a', 'w', 'x', 'n', 'u'},
                                        {'t', 'e', 'n', 'o', 'u'},
                                        {'t', 'i', 't', 'i', 'u'},
                                        {'w', 'e', 't', 'o', 'w'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("win");

  REQUIRE(result.word == "win");
  REQUIRE(result.char_positions.size() == 3);
  REQUIRE(result.char_positions.at(0).character == 'w');
  REQUIRE(result.char_positions.at(0).row == 1);
  REQUIRE(result.char_positions.at(0).col == 3);
  REQUIRE(result.char_positions.at(1).character == 'i');
  REQUIRE(result.char_positions.at(1).row == 2);
  REQUIRE(result.char_positions.at(1).col == 3);
  REQUIRE(result.char_positions.at(2).character == 'n');
  REQUIRE(result.char_positions.at(2).row == 3);
  REQUIRE(result.char_positions.at(2).col == 3);

  result = wss.FindWord("win", CheckDirection::kVertical);
  REQUIRE_FALSE(result.word.empty());
  REQUIRE_FALSE(result.char_positions.empty());
  result = wss.FindWord("win", CheckDirection::kHorizontal);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("win", CheckDirection::kLeftDiag);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("win", CheckDirection::kRightDiag);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("Left Diagonal Win", "[ldiag_win]") {
  std::vector<std::vector<char>> puzzle{{'d', 't', 'l', 'o', 'x', 'k'},
                                        {'k', 'l', 'a', 't', 'l', 'o'},
                                        {'l', 'a', 'k', 'a', 'k', 'm'},
                                        {'a', 'e', 't', 'l', 'x', 't'},
                                        {'t', 'e', 'a', 'o', 'a', 'u'},
                                        {'t', 't', 'k', 'l', 'a', 't'},
                                        {'t', 'e', 'k', 'o', 'x', 'u'}};
  WordSearchSolver wss(puzzle);

  WordLocation result = wss.FindWord("talk");

  REQUIRE(result.word == "talk");
  REQUIRE(result.char_positions.size() == 4);
  REQUIRE(result.char_positions.at(0).character == 't');
  REQUIRE(result.char_positions.at(0).row == 3);
  REQUIRE(result.char_positions.at(0).col == 5);
  REQUIRE(result.char_positions.at(1).character == 'a');
  REQUIRE(result.char_positions.at(1).row == 4);
  REQUIRE(result.char_positions.at(1).col == 4);
  REQUIRE(result.char_positions.at(2).character == 'l');
  REQUIRE(result.char_positions.at(2).row == 5);
  REQUIRE(result.char_positions.at(2).col == 3);
  REQUIRE(result.char_positions.at(3).character == 'k');
  REQUIRE(result.char_positions.at(3).row == 6);
  REQUIRE(result.char_positions.at(3).col == 2);

  result = wss.FindWord("talk", CheckDirection::kLeftDiag);
  REQUIRE_FALSE(result.word.empty());
  REQUIRE_FALSE(result.char_positions.empty());
  result = wss.FindWord("talk", CheckDirection::kHorizontal);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("talk", CheckDirection::kVertical);
  REQUIRE(result.word.empty());
  result = wss.FindWord("talk", CheckDirection::kRightDiag);
  REQUIRE(result.word.empty());
}

TEST_CASE("Right Diagonal Win", "[rdiag_win]") {
  std::vector<std::vector<char>> puzzle{{'d', 't', 't', 't', 'o', 'l'},
                                        {'h', 't', 's', 'o', 'l', 't'},
                                        {'c', 'o', 'l', 'o', 's', 's'},
                                        {'l', 'e', 't', 'o', 'l', 'o'},
                                        {'s', 'e', 'l', 'o', 's', 'l'},
                                        {'l', 't', 't', 'l', 'x', 't'},
                                        {'l', 'o', 'k', 'o', 'x', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("lost");

  REQUIRE(result.word == "lost");
  REQUIRE(result.char_positions.size() == 4);
  REQUIRE(result.char_positions.at(0).character == 'l');
  REQUIRE(result.char_positions.at(0).row == 2);
  REQUIRE(result.char_positions.at(0).col == 2);
  REQUIRE(result.char_positions.at(1).character == 'o');
  REQUIRE(result.char_positions.at(1).row == 3);
  REQUIRE(result.char_positions.at(1).col == 3);
  REQUIRE(result.char_positions.at(2).character == 's');
  REQUIRE(result.char_positions.at(2).row == 4);
  REQUIRE(result.char_positions.at(2).col == 4);
  REQUIRE(result.char_positions.at(3).character == 't');
  REQUIRE(result.char_positions.at(3).row == 5);
  REQUIRE(result.char_positions.at(3).col == 5);

  result = wss.FindWord("lost", CheckDirection::kRightDiag);
  REQUIRE_FALSE(result.word.empty());
  REQUIRE_FALSE(result.char_positions.empty());
  result = wss.FindWord("lost", CheckDirection::kHorizontal);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  result = wss.FindWord("lost", CheckDirection::kVertical);
  REQUIRE(result.word.empty());
  result = wss.FindWord("lost", CheckDirection::kLeftDiag);
  REQUIRE(result.word.empty());
}

TEST_CASE("Horizontal Word Wrap", "[horiz_word_wrap]") {
  std::vector<std::vector<char>> puzzle{{'p', 'l', 'u', 'm', ' ', 'p'},
                                        {'p', 'p', 'p', 'l', 'u', 'm'},
                                        {'p', 'a', 'l', 'i', 'x', 'p'},
                                        {'l', 'u', 'm', 'p', 'p', 'l'},
                                        {'u', 'm', 'p', 'p', 'l', 'u'},
                                        {'m', 'p', 'p', 'l', 'u', 'm'},
                                        {'m', 'p', 'p', 'p', 'p', 'l'},
                                        {'l', 'u', 'm', 'p', 'p', 'l'},
                                        {'u', 'm', 'p', 'p', 'l', 'u'},
                                        {'m', 'p', 'p', 'l', 'u', 'm'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("plump");
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("Vertical Word Wrap", "[vert_word_wrap]") {
  std::vector<std::vector<char>> puzzle{{'s', 's', 'o', 'r', 'c', 's'},
                                        {'s', 'c', 'p', 'l', 'r', 's'},
                                        {'s', 'r', 'l', 'i', 'o', 'o'},
                                        {'s', 'o', 'c', 'o', 'x', 'r'},
                                        {'s', 's', 'r', 'o', 's', 'c'},
                                        {'s', ' ', 'o', 'o', 's', 'u'},
                                        {'c', 's', 's', 'o', 'c', 'u'},
                                        {'r', 'o', 't', 'o', 'r', 'u'},
                                        {'o', 's', 't', 'l', 'o', 't'},
                                        {'s', 'c', 'r', 's', 's', 's'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("cross");
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("Left Diagonal Word Wrap", "[ldiag_word_wrap]") {
  std::vector<std::vector<char>> puzzle{{'b', 'l', 's', 'l', 'b', 's'},
                                        {'a', 't', 'a', 'l', 't', 'b'},
                                        {'b', 's', 'a', 'i', 'l', 'm'},
                                        {'t', 's', 'b', ' ', 'x', 't'},
                                        {'b', 'l', 'a', 'o', 's', 'u'},
                                        {'a', 's', 't', 'o', 's', 'u'},
                                        {'t', 'e', 't', 'o', 'c', 'l'},
                                        {'t', 'e', 't', 'o', 'a', 's'},
                                        {'t', 'e', 't', 's', 't', 'l'},
                                        {'t', 'e', 't', 'b', 'a', 'b'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("blast");
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("Right Diagonal Word Wrap", "[rdiag_word_wrap]") {
  std::vector<std::vector<char>> puzzle{{'t', 'e', 'o', 's', 'o', 't'},
                                        {'t', 'o', 't', 'a', 't', 'a'},
                                        {'p', 'a', 'a', 'i', 's', 't'},
                                        {'t', 'e', 'b', 's', 'x', 't'},
                                        {'t', 'l', 't', 'o', ' ', 'u'},
                                        {'t', 't', 't', 'o', 's', 't'},
                                        {'o', 'o', 't', 'o', 'c', 'u'},
                                        {'s', 'a', 'a', 'o', 'r', 'u'},
                                        {'o', 't', 's', 's', 'a', 't'},
                                        {'t', 'a', 't', 't', 's', 's'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("toast");
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
}

TEST_CASE("No Win", "[no_win]") {
  std::vector<std::vector<char>> puzzle{{'d', 'y', 'd', 'n', 'a', 'c'},
                                        {'t', 'y', 't', 'l', 'y', 'y'},
                                        {'t', 'o', 'd', 'd', 'd', 'd'},
                                        {'o', 'o', 'n', 'n', 'x', 'n'},
                                        {'a', 'a', 'a', 'o', 'a', 'a'},
                                        {'c', 'c', 't', 's', 'y', 'c'},
                                        {'t', 'e', 't', 'o', 'd', 'u'},
                                        {'t', 'e', 't', 'o', 'n', 'u'},
                                        {'t', 'e', 't', 'l', 'a', 't'},
                                        {'y', 'd', 'n', 'a', 'c', 's'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("candy", CheckDirection::kVertical);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  WordLocation result2 = wss.FindWord("candy", CheckDirection::kLeftDiag);
  REQUIRE(result2.word.empty());
  REQUIRE(result2.char_positions.empty());
  WordLocation result3 = wss.FindWord("candy", CheckDirection::kRightDiag);
  REQUIRE(result3.word.empty());
  REQUIRE(result3.char_positions.empty());
  WordLocation result4 = wss.FindWord("candy", CheckDirection::kHorizontal);
  REQUIRE(result4.word.empty());
  REQUIRE(result4.char_positions.empty());
  WordLocation result5 = wss.FindWord("candy");
  REQUIRE(result5.word.empty());
  REQUIRE(result5.char_positions.empty());
}

TEST_CASE("Skinny Puzzle", "[skinny_puzzle]") {
  std::vector<std::vector<char>> puzzle{{'d', 'd', 'h'},
                                        {'d', 'a', 'd'},
                                        {'r', 'd', 'd'},
                                        {'d', 'd', 'd'},
                                        {'r', 'a', 'h'},
                                        {'d', 'd', 'd'},
                                        {'h', 'a', 'r'},
                                        {'a', 'd', 'd'},
                                        {'r', 'e', 't'},
                                        {'d', 'd', 'n'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("hard", CheckDirection::kVertical);
  REQUIRE_FALSE(result.word.empty());
  REQUIRE_FALSE(result.char_positions.empty());
  WordLocation result2 = wss.FindWord("hard", CheckDirection::kLeftDiag);
  REQUIRE(result2.word.empty());
  REQUIRE(result2.char_positions.empty());
  WordLocation result3 = wss.FindWord("hard", CheckDirection::kRightDiag);
  REQUIRE(result3.word.empty());
  REQUIRE(result3.char_positions.empty());
  WordLocation result4 = wss.FindWord("hard", CheckDirection::kHorizontal);
  REQUIRE(result4.word.empty());
  REQUIRE(result4.char_positions.empty());
  WordLocation result5 = wss.FindWord("hard");
  REQUIRE_FALSE(result5.word.empty());
  REQUIRE_FALSE(result5.char_positions.empty());
}

TEST_CASE("Fat Puzzle", "[fat_puzzle]") {
  std::vector<std::vector<char>> puzzle{
      {'d', 'h', 'd', 'h', 'd', 'd', 'r', 'a', 'h'},
      {'d', 'a', 'd', 'd', 'a', 'd', 'd', 'a', 'h'},
      {'d', 'r', 'd', 'd', 'd', 'h', 'a', 'r', 'd'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("hard", CheckDirection::kVertical);
  REQUIRE(result.word.empty());
  REQUIRE(result.char_positions.empty());
  WordLocation result2 = wss.FindWord("hard", CheckDirection::kLeftDiag);
  REQUIRE(result2.word.empty());
  REQUIRE(result2.char_positions.empty());
  WordLocation result3 = wss.FindWord("hard", CheckDirection::kRightDiag);
  REQUIRE(result3.word.empty());
  REQUIRE(result3.char_positions.empty());
  WordLocation result4 = wss.FindWord("hard", CheckDirection::kHorizontal);
  REQUIRE_FALSE(result4.word.empty());
  REQUIRE_FALSE(result4.char_positions.empty());
  WordLocation result5 = wss.FindWord("hard");
  REQUIRE_FALSE(result5.word.empty());
  REQUIRE_FALSE(result5.char_positions.empty());
}

/////////////////////////////////////////////////////////////////////////////////////////////