//
// Created by garwi on 10/30/2020.
//

#include "gas_particle.h"
#include <math.h>

namespace idealgas {
/*
Gas_Particle::Gas_Particle(glm::vec2 &position, glm::vec2 &velocity) : position_(position), velocity_(velocity) {}
Gas_Particle::Gas_Particle(glm::vec2 position, glm::vec2 velocity) : position_(position), velocity_(velocity) {}
 */
Gas_Particle::Gas_Particle(glm::vec2 position, glm::vec2 velocity, float radius, const char* color) : position_(position),
                            velocity_(velocity), radius_(radius), color_(color){
  mass_ = 2 * radius_;
}
Gas_Particle::Gas_Particle(glm::vec2 &position, glm::vec2 &velocity, float radius, const char* color) : position_(position),
                            velocity_(velocity), radius_(radius), color_(color){
  mass_ = 2 * radius_;
}

void Gas_Particle::draw() {
  ci::gl::color(ci::Color(color_));
  ci::gl::drawSolidCircle(position_, radius_);
}

void Gas_Particle::Move() {
  position_ += velocity_;
}

void Gas_Particle::ReverseXDirection() {
  // 2x2 matrix denoting transformation of flipping x direction
  glm::mat2x2 flip_x(-1,0,0,1);
  velocity_ = flip_x * velocity_;
}

void Gas_Particle::ReverseYDirection() {
  // 2x2 matrix denoting transformation of flipping y direction
  glm::mat2x2 flip_x(1,0,0,-1);
  velocity_ = flip_x * velocity_;
}

void Gas_Particle::Handle_collision(glm::vec2 &other_velo, glm::vec2 &other_pos, float other_mass) {
  // Elastic collision equation
  glm::vec2 velo_diff = velocity_ - other_velo;
  glm::vec2 pos_diff = position_ - other_pos;
  float mass_term = other_mass*2/(mass_ + other_mass);
  velocity_ = velocity_ - mass_term*(glm::dot(velo_diff, pos_diff)/pow(glm::length(pos_diff), 2) * pos_diff);
}

const glm::vec2& Gas_Particle::GetPosition() const {
  return position_;
}

const glm::vec2& Gas_Particle::GetVelocity() const {
  return velocity_;
}

float Gas_Particle::GetRadius() const {
  return radius_;
}

float Gas_Particle::GetMass() const {
  return mass_;
}

void Gas_Particle::IncreaseSpeed() {
  if (glm::length(velocity_ *= 1.01f) < radius_/2)
    velocity_ *= 1.01f;
}

void Gas_Particle::DecreaseSpeed() {
  if (glm::length(velocity_ /= 1.01f) > 0)
    velocity_ /= 1.01f;
}

}

