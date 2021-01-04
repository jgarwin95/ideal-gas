//
// Created by garwi on 11/10/2020.
//
#include "cinder/gl/gl.h"
#include "cinder/Font.h"

#ifndef IDEAL_GAS_SRC_BUTTON_H_
#define IDEAL_GAS_SRC_BUTTON_H_

namespace idealgas {

class ColorDisplay {

 public:
  ColorDisplay(glm::vec2 top_left);
  void Draw();
  void Update(const char* pointer);

 private:
  const double kMargin = 10;
  const double kXDimension = 400;
  const double kYDimension = 100;
  std::vector<std::string> kStrings = {"KEY r => red", "KEY b => blue", "KEY g => green"};

  const char* current_color_;

  ci::Font text_font_;
  glm::vec2 top_left_;
  ci::Rectf outer_rect_;
  ci::Rectf inner_rect_;



};

}


#endif //IDEAL_GAS_SRC_BUTTON_H_
