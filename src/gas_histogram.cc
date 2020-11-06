//
// Created by garwi on 11/5/2020.
//

#include "gas_histogram.h"

GasHistogram::GasHistogram(const glm::vec2 &bottom_left_corner) {
  glm::vec2 padded_left = bottom_left_corner + glm::vec2(50, 0);
  glm::vec2 upper_right = padded_left + glm::vec2(kWindowSizeX, -kWindowSizeY);

  border_ = ci::Rectf(padded_left, upper_right);

  double bin_width = kWindowSizeX/kBinCount;

  for (int i = 0; i < kBinCount; i++) {
    // generate bin equally spaced apart.
    bins_.emplace_back(padded_left + glm::vec2(bin_width * i, 0), bin_width);
  }
}

void GasHistogram::Display() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(border_);

  for (Bin bin : bins_) {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(bin.rect_);
  }
}

const cinder::Rectf &GasHistogram::GetBorder() const {
  return border_;
}

GasHistogram::Bin::Bin(const glm::vec2 &bottom_left_corner, double width) {
  rect_ = ci::Rectf(bottom_left_corner, bottom_left_corner + glm::vec2(width, -10));
}
