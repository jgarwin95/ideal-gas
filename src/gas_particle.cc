//
// Created by garwi on 10/30/2020.
//

#include "gas_particle.h"
#include <math.h>

namespace idealgas {

Gas_Particle::Gas_Particle(glm::vec2 &position, glm::vec2 &velocity) : position_(position), velocity_(velocity) {}
Gas_Particle::Gas_Particle(glm::vec2 position, glm::vec2 velocity) : position_(position), velocity_(velocity) {}
Gas_Particle::Gas_Particle(glm::vec2 position, glm::vec2 velocity, float mass) : position_(position), velocity_(velocity),
                            mass_(mass){
  kRadius = mass_*10;
}

void Gas_Particle::draw() {
  ci::gl::color(ci::Color("red"));
  ci::gl::drawSolidCircle(position_, kRadius);
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
  float mass_term = mass_*2/(mass_ + other_mass);
  velocity_ = velocity_ - mass_term*(glm::dot(velo_diff, pos_diff)/pow(glm::length(pos_diff), 2) * pos_diff);
}

const glm::vec2& Gas_Particle::GetPosition() const {
  return position_;
}

const glm::vec2& Gas_Particle::GetVelocity() const {
  return velocity_;
}

float Gas_Particle::GetRadius() const {
  return kRadius;
}

float Gas_Particle::GetMass() const {
  return mass_;
}

void Gas_Particle::IncreaseSpeed() {
  if (glm::length(velocity_ *= 1.01f) < kRadius/2)
    velocity_ *= 1.01f;
}

void Gas_Particle::DecreaseSpeed() {
  if (glm::length(velocity_ /= 1.01f) > 0)
    velocity_ /= 1.01f;
}

}

