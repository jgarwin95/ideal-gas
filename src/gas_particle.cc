//
// Created by garwi on 10/30/2020.
//

#include "gas_particle.h"

namespace idealgas {

Gas_Particle::Gas_Particle(glm::vec2 &position, glm::vec2 &velocity) : position_(position), velocity_(velocity) {}
Gas_Particle::Gas_Particle(glm::vec2 position, glm::vec2 velocity) : position_(position), velocity_(velocity) {}

void Gas_Particle::draw() {
  ci::gl::color(ci::Color("red"));
  ci::gl::drawSolidCircle(position_, kRadius);
}

void Gas_Particle::Move() {
  position_ += velocity_;
}

void Gas_Particle::Reverse_X_direction() {
  // 2x2 matrix denoting transformation of flipping x direction
  glm::mat2x2 flip_x(-1,0,0,1);
  velocity_ = flip_x * velocity_;
}

void Gas_Particle::Reverse_Y_direction() {
  // 2x2 matrix denoting transformation of flipping y direction
  glm::mat2x2 flip_x(1,0,0,-1);
  velocity_ = flip_x * velocity_;
}

glm::vec2 Gas_Particle::Get_Position() {
  return position_;
}

float Gas_Particle::Get_radius() {
  return kRadius;
}

}

