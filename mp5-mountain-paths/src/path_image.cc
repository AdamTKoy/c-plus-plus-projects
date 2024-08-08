#include "path_image.hpp"

#include <cmath>
#include <fstream>
#include <limits>
#include <string>

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(dataset.Width()),
    height_(dataset.Height()),
    path_image_(image.GetImage()) {
  size_t row_idx = 0;
  size_t min_ele_index = 0;
  unsigned int min_ele_val = std::numeric_limits<int>::max();

  for (size_t row = 0; row < height_; row++) {
    path_image_.at(row).at(0) = kRed;
    row_idx = row;
    Path path(width_, row);
    path.SetLoc(0, row);
    for (size_t col = 0; col < width_ - 1; col++) {
      if (row_idx == 0 || row_idx == height_ - 1) {
        Update2Way(row_idx, col, dataset, path);
      } else {
        Update3Way(row_idx, col, dataset, path);
      }
    }
    paths_.push_back(path);
    if (path.EleChange() < min_ele_val) {
      min_ele_index = row;
      min_ele_val = path.EleChange();
    }
  }

  for (size_t col = 0; col < width_; col++) {
    std::vector<size_t> x = paths_.at(min_ele_index).GetPath();
    path_image_.at(x.at(col)).at(col) = kGreen;
  }
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (const auto& color_row : path_image_) {
    for (const auto& color : color_row) {
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << "\n";
  }
}

void PathImage::Update2Way(size_t& row,
                           size_t col,
                           const ElevationDataset& dataset,
                           Path& path) {
  int current = dataset.DatumAt(row, col);
  int next_fwd = dataset.DatumAt(row, col + 1);
  int next_other = 0;
  size_t row_idx = 0;

  if (row == 0) {
    next_other = dataset.DatumAt(row + 1, col + 1);
    row_idx = row + 1;
  } else {
    next_other = dataset.DatumAt(row - 1, col + 1);
    row_idx = row - 1;
  }
  int dif1 = abs(current - next_fwd);
  int dif2 = abs(current - next_other);

  if (dif1 <= dif2) {
    path_image_.at(row).at(col + 1) = kRed;
    path.SetLoc(col + 1, row);
    path.IncEleChange(dif1);
  } else {
    path_image_.at(row_idx).at(col + 1) = kRed;
    path.SetLoc(col + 1, row_idx);
    path.IncEleChange(dif2);
    row = row_idx;
  }
}

void PathImage::Update3Way(size_t& row,
                           size_t col,
                           const ElevationDataset& dataset,
                           Path& path) {
  int current = dataset.DatumAt(row, col);
  int next_up = dataset.DatumAt(row - 1, col + 1);
  int next_fwd = dataset.DatumAt(row, col + 1);
  int next_down = dataset.DatumAt(row + 1, col + 1);

  int dif1 = abs(current - next_fwd);
  int dif2 = abs(current - next_down);
  int dif3 = abs(current - next_up);

  if (dif1 <= dif2 && dif1 <= dif3) {
    path_image_.at(row).at(col + 1) = kRed;
    path.SetLoc(col + 1, row);
    path.IncEleChange(dif1);
  } else if (dif2 <= dif1 && dif2 <= dif3) {
    path_image_.at(row + 1).at(col + 1) = kRed;
    path.SetLoc(col + 1, row + 1);
    path.IncEleChange(dif2);
    row++;
  } else {
    path_image_.at(row - 1).at(col + 1) = kRed;
    path.SetLoc(col + 1, row - 1);
    path.IncEleChange(dif3);
    row--;
  }
}