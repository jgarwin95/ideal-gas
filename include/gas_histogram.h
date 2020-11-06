//
// Created by garwi on 11/5/2020.
//
#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_
#define IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_

class GasHistogram {
 public:
  // Constructors
  GasHistogram(const glm::vec2 &bottom_left_corner);

  // Methods
  void Display();
  void Update();

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
  const double kWindowSizeX = 300;
  const double kWindowSizeY = 240;
  const double kMargin = 50;
  const int kBinCount = 20;
  std::vector<Bin> bins_;
  ci::Rectf border_;
  int particle_count_ = 0;




};

#endif //IDEAL_GAS_INCLUDE_GAS_HISTOGRAM_H_
