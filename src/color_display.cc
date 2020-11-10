//
// Created by garwi on 11/10/2020.
//

#include "color_display.h"

namespace idealgas {

ColorDisplay::ColorDisplay(glm::vec2 top_left) : top_left_(top_left), current_color_("red"){
  outer_rect_ = ci::Rectf(top_left, top_left + glm::vec2(kXDimension, kYDimension));
  inner_rect_ = ci::Rectf(outer_rect_.getUpperLeft() + glm::vec2(kMargin, kMargin),
                          outer_rect_.getUpperLeft() + glm::vec2(kXDimension - kMargin, kYDimension - kMargin));

  text_font_ = ci::Font("Times New Roman", 30.0f);
}

void ColorDisplay::Draw() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(outer_rect_);

  ci::gl::color(ci::Color(current_color_));
  ci::gl::drawSolidRect(inner_rect_);

  int space = 1;
  for (std::string text : kStrings) {
    ci::gl::drawString(text, top_left_ + glm::vec2(kXDimension/3, kYDimension + (space*kMargin)), ci::Color("white"), text_font_);
    space += 2;
  }
}

void ColorDisplay::Update(const char* current_color) {
  current_color_ = current_color;
}

}
