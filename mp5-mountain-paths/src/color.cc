#include "color.hpp"

#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (red_ < 0 || red_ > kMaxCol || green_ < 0 || green_ > kMaxCol ||
      blue_ < 0 || blue_ > kMaxCol)
    throw std::runtime_error("Invalid color value(s).");
}

bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}