//
// Created by garwi on 11/5/2020.
//

#include "gas_histogram.h"
#include <algorithm>

namespace idealgas {

GasHistogram::GasHistogram(const glm::vec2 &bottom_left_corner, const char *color) : color_(color){
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
  for (Bin &bin : bins_) {
    ci::gl::color(ci::Color(color_));
    ci::gl::drawStrokedRect(bin.rect_);
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(border_);
}

void GasHistogram::Update(const std::vector<idealgas::Gas_Particle*> &particles) {
  // Clear existing bin information
  ClearBins();
  // Find the max velocity
  double max_speed = 0;
  for (Gas_Particle const *particle : particles) {
    double velo_magnitude = glm::length(particle->GetVelocity());
    if (velo_magnitude > max_speed) {
      max_speed = velo_magnitude;
    }
  }
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

  particle_count_ = 20;

  for (Bin &bin : bins_) {
    double height = kWindowSizeY * 0.8 * (bin.count_ / (particle_count_ * 1.0));
    // reset bin rect to new rect with adjusted height
    bin.rect_ = ci::Rectf(bin.rect_.getUpperLeft(), bin.rect_.getUpperLeft() + glm::vec2(bin_width_, -height));
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
