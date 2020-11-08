//
// Created by garwi on 11/5/2020.
//
#include "cinder/gl/gl.h"
#include "gas_particle.h"

#ifndef IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_
#define IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_

namespace idealgas {

class GasHistogram {
 public:
  // Constructors
  GasHistogram(const glm::vec2 &bottom_left_corner, const char *color);

  // Methods
  void Display();
  void Update(const std::vector<idealgas::Gas_Particle*> &particles);

  // Getters & Setters
  const cinder::Rectf &GetBorder() const;

  // Inner struct
  struct Bin {
    Bin(const glm::vec2 &bottom_left_corner, double width);
    int count_ = 0;
    ci::Rectf rect_;
    int x_loc_;
    int y_loc_;
  };

 private:
  const char *color_;
  const double kWindowSizeX = 300;
  const double kWindowSizeY = 240;
  const double kMargin = 50;
  const int kBinCount = 20;
  double bin_width_;
  std::vector<Bin> bins_;
  ci::Rectf border_;
  int particle_count_ = 0;

  void ClearBins();
};

}

#endif //IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_
