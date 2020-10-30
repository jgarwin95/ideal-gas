#include <gas_container.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Gas_container::Gas_container(const glm::vec2 &top_left_corner, double container_size) :
  top_left_corner_(top_left_corner), container_size_(container_size){
  vec2 bottom_right =
      top_left_corner_ + vec2(container_size_, container_size_);

  container_rect_ = ci::Rectf(top_left_corner_, bottom_right);
}

void Gas_container::Draw() const {

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_rect_);
}

}  // namespace visualizer

}  // namespace idealgas
