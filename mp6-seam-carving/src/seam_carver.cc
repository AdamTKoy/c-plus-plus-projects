#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// returns the instance's image_
const ImagePPM& SeamCarver::GetImage() const { return image_; }

// returns the image's height
int SeamCarver::GetHeight() const { return height_; }

// returns the image's width
int SeamCarver::GetWidth() const { return width_; }

// can assume row/col always in bounds
int SeamCarver::GetEnergy(int row, int col) const {
  int next_row = row + 1;
  int prev_row = row - 1;
  int next_col = col + 1;
  int prev_col = col - 1;

  if (row == 0) {
    prev_row = height_ - 1;
  } else if (row == height_ - 1) {
    next_row = 0;
  }

  if (col == 0) {
    prev_col = width_ - 1;
  } else if (col == width_ - 1) {
    next_col = 0;
  }

  Pixel prev_row_px = image_.GetPixel(prev_row, col);
  Pixel next_row_px = image_.GetPixel(next_row, col);
  Pixel prev_col_px = image_.GetPixel(row, prev_col);
  Pixel next_col_px = image_.GetPixel(row, next_col);
  int row_red = prev_row_px.GetRed() - next_row_px.GetRed();
  int row_green = prev_row_px.GetGreen() - next_row_px.GetGreen();
  int row_blue = prev_row_px.GetBlue() - next_row_px.GetBlue();
  int col_red = prev_col_px.GetRed() - next_col_px.GetRed();
  int col_green = prev_col_px.GetGreen() - next_col_px.GetGreen();
  int col_blue = prev_col_px.GetBlue() - next_col_px.GetBlue();
  int energy = (row_red * row_red) + (row_green * row_green) +
               (row_blue * row_blue) + (col_red * col_red) +
               (col_green * col_green) + (col_blue * col_blue);
  return energy;
}

// FUNCTION TO IMPLEMENT (NOT MINE)
// Returns pointer to array with list of ROW INDICES
int* SeamCarver::GetHorizontalSeam() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
  }
  // best is uppermost ROW INDEX of min value in col 0
  int best = FindHorizontalMin(values);

  int* track = new int[width_];
  HorizontalTrack(values, track, best);

  for (int row = 0; row < height_; row++) {
    delete[] values[row];
  }
  delete[] values;
  values = nullptr;

  return track;
}

int SeamCarver::FindHorizontalMin(int* values[]) const {
  // Calculate energies for entire last column
  for (int row_idx = 0; row_idx < height_; row_idx++) {
    values[row_idx][width_ - 1] = GetEnergy(row_idx, width_ - 1);
  }

  int back = 0, back_lower = 0, back_upper = 0;
  int energy = 0, plus = 0;

  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      energy = GetEnergy(row, col);
      back = values[row][col + 1];
      if (row == 0) {
        back_lower = values[row + 1][col + 1];
        plus = BestValueTwo(back, back_lower);
      } else if (row == height_ - 1) {
        back_upper = values[row - 1][col + 1];
        plus = BestValueTwo(back, back_upper);
      } else {
        back_upper = values[row - 1][col + 1];
        back_lower = values[row + 1][col + 1];
        plus = BestValueThree(back, back_upper, back_lower);
      }
      values[row][col] = energy + plus;
    }
  }
  // returns uppermost ROW INDEX of least value
  // in 0th column
  return (BestHoriz(values));
}

int SeamCarver::BestHoriz(int** vals) const {
  int min = vals[0][0];
  int min_idx = 0;
  for (int row = 1; row < height_; row++) {
    if (vals[row][0] < min) {
      min = vals[row][0];
      min_idx = row;
    }
  }
  return min_idx;
}

void SeamCarver::HorizontalTrack(int** values, int* track, int best) const {
  int idx = best;  // index of starting ROW (col 0)
  track[0] = idx;
  int ahead = 0, ahead_up = 0, ahead_down = 0;

  for (int col = 1; col < width_; col++) {
    ahead = values[idx][col];
    if (idx == 0) {  // FIRST ROW
      ahead_down = values[idx + 1][col];
      if (ahead_down < ahead) {
        idx++;
      }
    }

    else if (idx == height_ - 1) {  // LAST ROW
      ahead_up = values[idx - 1][col];
      if (ahead_up < ahead) {
        idx--;
      }
    }

    else {  // MID-ROW
      ahead_down = values[idx + 1][col];
      ahead_up = values[idx - 1][col];

      if (ahead_up < ahead && ahead_up <= ahead_down) {
        idx--;
      } else if (ahead_down < ahead && ahead_down < ahead_up) {
        idx++;
      }
    }
    track[col] = idx;
  }
}

// FUNCTION TO IMPLEMENT (NOT MINE)
// Returns pointer to array with list of COLUMN INDICES
int* SeamCarver::GetVerticalSeam() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
  }
  // best is COL INDEX of minimum value
  // in TOP (0th) ROW
  int best = FindVerticalMin(values);

  int* track = new int[height_];
  VerticalTrack(values, track, best);

  for (int row = 0; row < height_; row++) {
    delete[] values[row];
  }
  delete[] values;
  values = nullptr;

  return track;
}

int SeamCarver::FindVerticalMin(int** values) const {
  // Calculate energies only for BOTTOM ROW
  for (int col = 0; col < width_; col++) {
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }

  int down = 0, down_right = 0, down_left = 0;
  int energy = 0, plus = 0;

  // now starting from second-to-last row:
  for (int row = height_ - 2; row >= 0; row--) {
    // go through each cell of the row
    for (int col = 0; col < width_; col++) {
      energy = GetEnergy(row, col);  // energy of current cell
      down = values[row + 1][col];
      if (col == 0) {
        down_right = values[row + 1][col + 1];
        plus = BestValueTwo(down, down_right);
      } else if (col == width_ - 1) {
        down_left = values[row + 1][col - 1];
        plus = BestValueTwo(down, down_left);
      } else {
        down_right = values[row + 1][col + 1];
        down_left = values[row + 1][col - 1];
        plus = BestValueThree(down, down_left, down_right);
      }
      values[row][col] = energy + plus;
    }
  }
  // returns COLUMN INDEX of lowest value in 0th row
  int min = values[0][0];
  int min_idx = 0;
  for (int col = 1; col < width_; col++) {
    if (values[0][col] < min) {
      min = values[0][col];
      min_idx = col;
    }
  }
  return min_idx;
}

void SeamCarver::VerticalTrack(int** values, int* track, int best) const {
  // best is leftmost COL INDEX of min value in row 0
  int idx = best;  // TO FIX
  track[0] = idx;
  int next = 0, next_left = 0, next_right = 0;

  for (int row = 1; row < height_; row++) {
    next = values[row][idx];
    if (idx == 0) {  // FIRST COLUMN
      next_right = values[row][idx + 1];
      if (next_right < next) {
        idx++;
      }
    }

    else if (idx == width_ - 1) {  // LAST COLUMN
      next_left = values[row][idx - 1];
      if (next_left < next) {
        idx--;
      }
    }

    else {  // MIDDLE COLUMNS
      next_right = values[row][idx + 1];
      next_left = values[row][idx - 1];

      if (next_left < next && next_left <= next_right) {
        idx--;
      } else if (next_right < next && next_right < next_left) {
        idx++;
      }
    }
    track[row] = idx;
  }
}

// removes one horizontal seam in image_. example:
//
// image_ before:
//  0 | 1 | 2 | 3
// ---+---+---+---
//  4 | 5 | 6 | 7
// ---+---+---+---
//  8 | 9 | 10| 11
//
// seam to remove:
//    | x |   |
// ---+---+---+---
//  x |   | x |
// ---+---+---+---
//    |   |   | x
//
// image_ after:
//  0 | 5 | 2 | 3
// ---+---+---+---
//  8 | 9 | 10| 7
void SeamCarver::RemoveHorizontalSeam() {
  int* hs = GetHorizontalSeam();

  ImagePPM temp;
  temp.PopulateObject(width_, height_ - 1, image_.GetMaxColorValue());

  int row_idx = 0;
  Pixel p = {0, 0, 0};

  for (int col = 0; col < width_; col++) {
    for (int row = 0; row < height_; row++) {
      if (row != hs[col]) {
        p = image_.GetPixel(row, col);
        temp.SetPixel(p, row_idx, col);
        row_idx++;
      }
    }
    row_idx = 0;
  }

  SetImage(temp);

  delete[] hs;
  hs = nullptr;
  temp.~ImagePPM();
  // is temp automatically deallocated b/c of destruction definition?
}

// removes one vertical seam in image_. example:
//
// image_ before:
//  0 | 1 | 2 | 3
// ---+---+---+---
//  4 | 5 | 6 | 7
// ---+---+---+---
//  8 | 9 | 10| 11
//
// seam to remove:
//    | x |   |
// ---+---+---+---
//    |   | x |
// ---+---+---+---
//    |   | x |
//
// image_ after:
//  0 | 2 | 3
// ---+---+---
//  4 | 5 | 7
// ---+---+---
//  8 | 9 | 11
void SeamCarver::RemoveVerticalSeam() {
  // list of COLUMN INDICES
  int* vs = GetVerticalSeam();
  // remove a column of image_
  ImagePPM temp;
  temp.PopulateObject(width_ - 1, height_, image_.GetMaxColorValue());

  int col_idx = 0;
  Pixel p = {0, 0, 0};

  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col++) {
      if (col != vs[row]) {
        p = image_.GetPixel(row, col);
        temp.SetPixel(p, row, col_idx);
        col_idx++;
      }
    }
    col_idx = 0;
  }

  SetImage(temp);

  delete[] vs;
  vs = nullptr;
  temp.~ImagePPM();
}

int SeamCarver::BestValueTwo(int same_idx, int other_idx) const {
  // same row/col index always takes preference
  if (other_idx < same_idx) {
    return other_idx;
  }
  return same_idx;
}

int SeamCarver::BestValueThree(int same_idx,
                               int other_idx_1,
                               int other_idx_2) const {
  // same row/col index always takes preference
  if (same_idx <= other_idx_1 && same_idx <= other_idx_2) {
    return same_idx;
  }
  // other_idx_1 must be higher priority option when calling
  // LEFT or TOP
  if (other_idx_1 <= other_idx_2) {
    return other_idx_1;
  }
  return other_idx_2;  // RIGHT or BOTTOM
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
