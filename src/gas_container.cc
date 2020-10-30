#include <gas_container.h>

namespace idealgas {

namespace container {

using glm::vec2;

Gas_container::Gas_container(const glm::vec2 &top_left_corner, double container_size) :
  top_left_corner_(top_left_corner), container_size_(container_size){
  vec2 bottom_right =
      top_left_corner_ + vec2(container_size_, container_size_);

  container_rect_ = ci::Rectf(top_left_corner_, bottom_right);
  // place single particle in the middle of the container
  particles_.emplace_back(top_left_corner + glm::vec2(container_size/2, container_size/2),
                          glm::vec2(5, -2)); // vector moving in the positive x direction
}

void Gas_container::Draw() const {

  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_rect_);

  // draw each particle
  for (Gas_Particle particle : particles_) {
    particle.draw();
  }
}

void Gas_container::Update()  {

  // update each particle
  for (Gas_Particle& particle : particles_) {
    // Move particle each frame
    particle.Move();
    float radius = particle.Get_radius();
    // check if the particle is touching a left/right wall
    if ((particle.Get_Position().x  + radius >= container_rect_.x2) ||
    (particle.Get_Position().x  - radius <= container_rect_.x1)) {
      // Flip x direction
      particle.Reverse_X_direction();
    }
    // check if the particle is touching a top/bottom wall
    if ((particle.Get_Position().y  + radius >= container_rect_.y2) ||
        (particle.Get_Position().y  - radius <= container_rect_.y1)) {
      // Flip y direction
      particle.Reverse_Y_direction();
    }
  }
}


}  // namespace container

}  // namespace idealgas
