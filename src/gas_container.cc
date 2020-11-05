#include <gas_container.h>
#include <math.h>

namespace idealgas {

namespace container {

using glm::vec2;

Gas_container::Gas_container(const glm::vec2 &top_left_corner, double container_size) :
  top_left_corner_(top_left_corner), container_size_(container_size){
  vec2 bottom_right =
      top_left_corner_ + vec2(container_size_, container_size_);

  container_rect_ = ci::Rectf(top_left_corner_, bottom_right);
  // place single particle in the middle of the container

}

void Gas_container::Generate_particle() {
  std::cout << "particle is generated!" << std::endl;
  particles_.emplace_back(top_left_corner_ + glm::vec2(container_size_/2, container_size_/2),
                          glm::vec2(3, -2));
}

void Gas_container::Generate_particle(int x_loc, int y_loc, int x_vel, int y_vel) {
  particles_.emplace_back(glm::vec2(x_loc, y_loc),
                          glm::vec2(x_vel, y_vel)); // vector moving in the positive x direction
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
  for (Gas_Particle& particle : particles_) {
    // Move each particle to it's final position for this frame
    particle.Move();
  }

  int particle_counter = 0;
  // Handle any collisions associated with those final positions
  for (Gas_Particle& particle : particles_) {

    float radius = particle.GetRadius();

    // check if the particle is touching a left/right wall
    if (((particle.GetPosition().x  - radius <= container_rect_.x1) && CheckOppositeDirection(particle, "left")) ||
    ((particle.GetPosition().x  + radius >= container_rect_.x2) && CheckOppositeDirection(particle, "right"))) {
      // Flip x direction
      particle.ReverseXDirection();
    }
    // check if the particle is touching a top/bottom wall
    if (((particle.GetPosition().y  + radius >= container_rect_.y2) && CheckOppositeDirection(particle, "bottom")) ||
        ((particle.GetPosition().y  - radius <= container_rect_.y1) && CheckOppositeDirection(particle, "top"))) {
      // Flip y direction
      particle.ReverseYDirection();
    }

    for (size_t i = particle_counter + 1; i < particles_.size(); i++) {
      Gas_Particle &other = particles_.at(i);
      // If they are touching and were heading in the same direction handle collision
      if (Check_collision(particle, other) && CheckOppositeDirection(particle, other)) {
        HandleCollision(particle, other);
      }
    }
    // Increment current particle number
    particle_counter++;
  }
}

void Gas_container::HandleCollision(Gas_Particle &particle_1, Gas_Particle &particle_2) {
  // Save initial state of particles
  glm::vec2 vi_1 = particle_1.GetVelocity();
  glm::vec2 vi_2 = particle_2.GetVelocity();
  glm::vec2 xi_1 = particle_1.GetPosition();
  glm::vec2 xi_2 = particle_2.GetPosition();
  float m1 = particle_1.GetMass();
  float m2 = particle_2.GetMass();
  // Alter velocities based on previously saved state
  particle_1.Handle_collision(vi_2, xi_2, m2);
  particle_2.Handle_collision(vi_1, xi_1, m1);
}

bool Gas_container::Check_collision(const Gas_Particle &particle_1, const Gas_Particle &particle_2) {
  glm::vec2 pos1 = particle_1.GetPosition();
  glm::vec2 pos2 = particle_2.GetPosition();
  // return if the sum of the radii is less than the distance between the centers of the two particles
  return (particle_1.GetRadius() + particle_2.GetRadius() >= glm::distance(particle_1.GetPosition(), particle_2.GetPosition()));
}

bool Gas_container::CheckOppositeDirection(const Gas_Particle &particle_1, const Gas_Particle &particle_2) const {
  float result = glm::dot(particle_1.GetVelocity() - particle_2.GetVelocity(), particle_1.GetPosition() - particle_2.GetPosition());
  return (result < 0);
}

bool Gas_container::CheckOppositeDirection(const Gas_Particle &particle, std::string&& direction) const {
  glm::vec2 wall_position;
  if (direction == "left")
    wall_position = glm::vec2(container_rect_.getX1(), particle.GetPosition().y);
  else if (direction == "right")
    wall_position = glm::vec2(container_rect_.getX2(), particle.GetPosition().y);
  else if (direction == "top")
    wall_position = glm::vec2(particle.GetPosition().x, container_rect_.getY1());
  else if (direction == "bottom")
    wall_position = glm::vec2(particle.GetPosition().x, container_rect_.getY2());

  float result = glm::dot(particle.GetVelocity(), particle.GetPosition() - wall_position);

  return result < 0;
}

const std::vector<Gas_Particle>& Gas_container::Get_particles() const {
  return particles_;
}

void Gas_container::Clear() {
  particles_.clear();
}

void Gas_container::IncreaseParticleSpeed() {
  for (Gas_Particle &particle : particles_) {
    particle.IncreaseSpeed();
  }
}

void Gas_container::DecreaseParticleSpeed() {
  for (Gas_Particle &particle : particles_) {
    particle.DecreaseSpeed();
  }
}

}  // namespace container

}  // namespace idealgas
