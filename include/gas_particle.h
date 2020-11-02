//
// Created by garwi on 10/30/2020.
//

#ifndef IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_
#define IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_

#include "cinder/gl/gl.h"

namespace idealgas {

class Gas_Particle {
 public:
  // Constructor that takes references
  Gas_Particle(glm::vec2 &position, glm::vec2 &velocity);
  // Constructor that takes rvalues
  Gas_Particle(glm::vec2 position, glm::vec2 velocity);
  void draw();
  void Move();
  void ReverseXDirection();
  void ReverseYDirection();

  // Getters & Setters
  const glm::vec2 &GetPosition() const;
  const glm::vec2 &GetVelocity() const;
  float GetRadius() const;

  void Handle_collision(glm::vec2 &other_velo, glm::vec2 &other_pos);

  void IncreaseSpeed();
 private:
  glm::vec2 position_;
  glm::vec2 velocity_;

  std::string kColor = "red";
  float kRadius = 10;
  //glm::mat2x2 kFlip_x(-1,0,0,1); why can't I specify this matrix as a constant member variable... (ask TA)
};

}


#endif //IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_
