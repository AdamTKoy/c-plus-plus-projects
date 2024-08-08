#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <limits>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) throw std::runtime_error("Unable to open file.");

  int current = 0;
  max_ele_ = std::numeric_limits<int>::min();
  min_ele_ = std::numeric_limits<int>::max();
  std::vector<int> row_values;

  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      if (ifs.fail()) {
        throw std::runtime_error("Invalid or missing input.");
      }

      ifs >> current;
      if (current > max_ele_) max_ele_ = current;
      if (current < min_ele_) min_ele_ = current;
      row_values.push_back(current);
    }
    data_.push_back(row_values);
    row_values.clear();
  }

  ifs >> current;
  if (ifs.good())
    throw std::runtime_error("Values exceed provided dimensions.");
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}