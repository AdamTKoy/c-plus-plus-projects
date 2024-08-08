#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  Color t;
  std::vector<Color> temp;
  int shade_of_gray = 0;

  if (dataset.MaxEle() == dataset.MinEle()) {
    t = {0, 0, 0};
    std::vector<std::vector<Color>> temp_image(height_,
                                               std::vector<Color>(width_, t));
    image_ = temp_image;
  } else {
    for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col < width_; col++) {
        int a = dataset.DatumAt(row, col) - dataset.MinEle();
        int b = dataset.MaxEle() - dataset.MinEle();
        double c = double(a) / double(b);
        shade_of_gray = std::round(c * kMaxColorValue);
        t = {shade_of_gray, shade_of_gray, shade_of_gray};
        temp.push_back(t);
      }
      image_.push_back(temp);
      temp.clear();
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset ed1(filename, width_, height_);
  Color t;
  std::vector<Color> temp;
  int shade_of_gray = 0;

  if (ed1.MaxEle() == ed1.MinEle()) {
    t = {0, 0, 0};
    std::vector<std::vector<Color>> temp_image(height_,
                                               std::vector<Color>(width_, t));
    image_ = temp_image;
  } else {
    for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col < width_; col++) {
        int a = ed1.DatumAt(row, col) - ed1.MinEle();
        int b = ed1.MaxEle() - ed1.MinEle();
        double c = double(a) / double(b);
        shade_of_gray = std::round(c * kMaxColorValue);
        t = {shade_of_gray, shade_of_gray, shade_of_gray};
        temp.push_back(t);
      }
      image_.push_back(temp);
      temp.clear();
    }
  }
}

size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (const auto& color_row : image_) {
    for (const auto& color : color_row) {
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << "\n";
  }
}