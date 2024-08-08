#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

  void Update2Way(size_t& row,
                  size_t col,
                  const ElevationDataset& dataset,
                  Path& path);
  void Update3Way(size_t& row,
                  size_t col,
                  const ElevationDataset& dataset,
                  Path& path);

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  const Color kRed = {252, 25, 63};
  const Color kGreen = {31, 253, 13};
};

#endif