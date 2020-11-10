//
// Created by garwi on 11/5/2020.
//

#include "gas_histogram.h"
#include "cinder/Font.h"

namespace idealgas {

GasHistogram::GasHistogram(const glm::vec2 &bottom_left_corner, const char *color) : color_(color),
                          bottom_left_(bottom_left_corner){
  glm::vec2 padded_left = bottom_left_corner + glm::vec2(kMargin, 0);
  glm::vec2 upper_right = padded_left + glm::vec2(kWindowSizeX, -kWindowSizeY);

  border_ = ci::Rectf(padded_left, upper_right);

  bin_width_ = kWindowSizeX / kBinCount;

  for (int i = 0; i < kBinCount; i++) {
    // generate bin equally spaced apart.
    bins_.emplace_back(padded_left + glm::vec2(bin_width_ * i, 0), bin_width_);
  }
}

void GasHistogram::Display() {
  ci::Font text("Times New Roman", 30.0f);
  ci::gl::drawStringCentered("Speed", bottom_left_ + glm::vec2(kMargin + kWindowSizeX/2, 0), ci::Color("white"), text);

  for (Bin &bin : bins_) {
    ci::gl::color(ci::Color(color_));
    ci::gl::drawStrokedRect(bin.rect_);
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(border_);
}

void GasHistogram::Update(const std::vector<idealgas::Gas_Particle*> &particles, double max_speed) {
  // Clear existing bin information
  ClearBins();

  double bin_width = max_speed/kBinCount;

  // Place into appropriate bin
  for (Gas_Particle const *particle : particles) {
    for (int i = 0; i < kBinCount; i++) {
      if ((glm::length(particle->GetVelocity()) >= i * bin_width) && (glm::length(particle->GetVelocity()) <= bin_width * (i + 1))) {
        // increment bin count
        bins_.at(i).count_++;
        // particle has been added break out of loop
        break;
      }
    }
    // increment total count
    particle_count_++;
  }

  for (Bin &bin : bins_) {
    // scale height of bin to window size
    double height = kWindowSizeY * (bin.count_ / (particle_count_ * 1.0));
    // reset bin rect to new rect with adjusted height
    bin.rect_ = ci::Rectf(glm::vec2(bin.rect_.x1, bin.rect_.y1), glm::vec2(bin.rect_.x1, bin.rect_.y1) + glm::vec2(bin_width_, -height));
  }
}

const cinder::Rectf &GasHistogram::GetBorder() const {
  return border_;
}

void GasHistogram::ClearBins() {
  for (Bin &bin : bins_) {
    bin.count_ = 0;
  }
  particle_count_ = 0;
}

GasHistogram::Bin::Bin(const glm::vec2 &bottom_left_corner, double width) {
  rect_ = ci::Rectf(bottom_left_corner, bottom_left_corner + glm::vec2(width, 0));
}

} // namespace idealgas
