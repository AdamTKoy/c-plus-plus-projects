// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);

  REQUIRE(AreEqual(solution, student.board));
  REQUIRE((sizeof(student.board)/sizeof(student.board[0])) == (sizeof(solution)/sizeof(solution[0])));
}

TEST_CASE("Drop disk", "[drop_disk]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kEmpty, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);

  REQUIRE(AreEqual(solution, student.board));
  
}

TEST_CASE("No Win Partial Board", "[no_win_partial_board]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);

  REQUIRE(AreEqual(solution, student.board));

  SECTION("kPlayer1 no win") {
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }

  SECTION("kPlayer2 no win") {
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

TEST_CASE("No Win Full Board", "[no_win_full_board]") {
  // clang-format off
    DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1}, 
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1}, 
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);

  REQUIRE(AreEqual(solution, student.board));

  SECTION("kPlayer1 no win") {
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    
    REQUIRE_FALSE(CheckForWinner(student, DiskType(82)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(82), WinningDirection(0)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(82), WinningDirection(1)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(82), WinningDirection(2)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(82), WinningDirection(3)));
  }

  SECTION("kPlayer2 no win") {
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    
    REQUIRE_FALSE(CheckForWinner(student, DiskType(66)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(66), WinningDirection(0)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(66), WinningDirection(1)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(66), WinningDirection(2)));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType(66), WinningDirection(3)));
  }
}

TEST_CASE("Horizontal Win", "[horizontal_win]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);

  REQUIRE(AreEqual(solution, student.board));

  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Vertical Win", "[vertical_win]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);

  REQUIRE(AreEqual(solution, student.board));

  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
}

TEST_CASE("Right Diagonal Win", "[right_diagonal_win]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);

  REQUIRE(AreEqual(solution, student.board));

  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Left Diagonal Win", "[left_diag_win]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);

  REQUIRE(AreEqual(solution, student.board));

  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
}

TEST_CASE("Invalid Column Error", "[invalid_col_error]") {
  // clang-format off

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  SECTION("player 1") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 7),
                    std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -1),
                    std::runtime_error);
  }

  SECTION("player 2") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1),
                    std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 7),
                    std::runtime_error);
  }

  SECTION("empty") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 7),
                    std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, -1),
                    std::runtime_error);
  }
}

TEST_CASE("Drop on Full Column Error", "[drop_full_col_error]") {
  // clang-format off

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);

  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);

  SECTION("player 1") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 1), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 2), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 3), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 4), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 5), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 6), std::runtime_error);
  }

  SECTION("player 2") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 0), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 1), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 2), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 3), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 4), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 5), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 6), std::runtime_error);
  }

  SECTION("empty") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 0), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 1), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 2), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 3), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 4), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 5), std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kEmpty, 6), std::runtime_error);
  }
}

TEST_CASE("Bounds Checking", "[bounds_checking]") {
  // clang-format off

  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);

  SECTION("only column out of bounds") {
    REQUIRE_FALSE(BoardLocationInBounds(0, 7));
    REQUIRE_FALSE(BoardLocationInBounds(5, -1));
  }

  SECTION("only row out of bounds") {
    REQUIRE_FALSE(BoardLocationInBounds(-1, 0));
    REQUIRE_FALSE(BoardLocationInBounds(6, 6));
  }

  SECTION("both row and column out of bounds") {
    REQUIRE_FALSE(BoardLocationInBounds(6, 7));
    REQUIRE_FALSE(BoardLocationInBounds(6, -1));
    REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
    REQUIRE_FALSE(BoardLocationInBounds(-1, 7));
  }

  SECTION("both row and column in bounds") {
    REQUIRE(BoardLocationInBounds(0, 0));
    REQUIRE(BoardLocationInBounds(5, 6));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////