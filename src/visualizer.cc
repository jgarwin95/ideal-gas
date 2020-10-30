#include <visualizer.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Sketchpad::Sketchpad(const vec2& top_left_corner, double sketchpad_size)
    : top_left_corner_(top_left_corner), sketchpad_size_(sketchpad_size){
}

void Sketchpad::Draw() const {

  // draw container border
  vec2 bottom_right =
      top_left_corner_ + vec2(sketchpad_size_, sketchpad_size_);
  ci::Rectf idea_gas_container(top_left_corner_, bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(idea_gas_container);
}

}  // namespace visualizer

}  // namespace idealgas
