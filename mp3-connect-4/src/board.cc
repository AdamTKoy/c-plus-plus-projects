#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col < 0 || col > Board::kBoardWidth - 1) {
    throw std::runtime_error("Invalid column.");
  }

  if (b.board[Board::kBoardHeight - 1][col] != DiskType::kEmpty) {
    throw std::runtime_error("Column already full.");
  }

  bool filled = false;
  int row = 0;

  while (!filled) {
    if (b.board[row][col] == DiskType::kEmpty) {
      b.board[row][col] = disk;
      filled = true;
    } else
      row++;
  }
  
}

bool CheckForWinner(const Board& b, DiskType disk) {
  return (SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
          SearchForWinner(b, disk, WinningDirection::kVertical) ||
          SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
          SearchForWinner(b, disk, WinningDirection::kRightDiag));
}

bool SearchForWinner(const Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal)
    return CheckHorizontal(b, disk);
  if (to_check == WinningDirection::kVertical) return CheckVertical(b, disk);
  if (to_check == WinningDirection::kLeftDiag) return CheckLeftDiag(b, disk);
  if (to_check == WinningDirection::kRightDiag)
    return CheckRightDiag(b, disk);
  return false;
}

bool CheckHorizontal(const Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    int consec = 0;
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk) {
        consec++;
        if (consec == 4) return true;
      } else
        consec = 0;
    }
  }
  return false;
}

bool CheckVertical(const Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    int consec = 0;
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk) {
        consec++;
        if (consec == 4) return true;
      } else
        consec = 0;
    }
  }
  return false;
}
bool CheckLeftDiag(const Board& b, DiskType disk) {
  int start_col = 3;
  int current_col = start_col;
  int current_row = 0;
  int consecutive = 0;
  bool looking = true;
  constexpr int kWinNum = 4;
  int last_col_row_idx = 1;

  int diags_to_check =
      Board::kBoardWidth + Board::kBoardHeight - (kWinNum * 2 - 1);

  for (int idx = 0; idx < diags_to_check; idx++) {
    looking = BoardLocationInBounds(current_row, current_col);
    while (looking) {
      if (b.board[current_row][current_col] == disk) {
        consecutive++;
        if (consecutive == kWinNum) return true;
      } else
        consecutive = 0;

      current_col -= 1;
      current_row += 1;
      looking = BoardLocationInBounds(current_row, current_col);
    }

    consecutive = 0;

    if (start_col != (Board::kBoardWidth - 1)) {
      current_row = 0;
      start_col += 1;

    } else {
      current_row = last_col_row_idx;
      last_col_row_idx++;
    }
    current_col = start_col;
  }
  return false;
}

bool CheckRightDiag(const Board& b, DiskType disk) {
  int start_col = Board::kBoardWidth - 4;
  int current_col = start_col;
  int current_row = 0;
  int consecutive = 0;
  bool looking = true;
  constexpr int kWinNum = 4;
  int first_col_row_idx = 1;

  int diags_to_check =
      Board::kBoardWidth + Board::kBoardHeight - (kWinNum * 2 - 1);

  for (int idx = 0; idx < diags_to_check; idx++) {
    looking = BoardLocationInBounds(current_row, current_col);
    while (looking) {
      if (b.board[current_row][current_col] == disk) {
        consecutive++;
        if (consecutive == kWinNum) return true;
      } else
        consecutive = 0;

      current_row++;
      current_col++;
      looking = BoardLocationInBounds(current_row, current_col);
    }

    consecutive = 0;

    if (start_col != 0) {
      current_row = 0;
      start_col -= 1;

    } else {
      current_row = first_col_row_idx;
      first_col_row_idx++;
    }
    current_col = start_col;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return ((row >= 0 && row < Board::kBoardHeight) &&
          (col >= 0 && col < Board::kBoardWidth));
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}