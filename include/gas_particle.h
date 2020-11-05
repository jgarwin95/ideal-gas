//
// Created by garwi on 10/30/2020.
//

#ifndef IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_
#define IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_

#include "cinder/gl/gl.h"

namespace idealgas {

class Gas_Particle {
 public:
  /**
   * Create a particle with specified position and velocity vectors
   * @param position 2d vector denoting position
   * @param velocity 2d vector denoting velocity
   */
  Gas_Particle(glm::vec2 &position, glm::vec2 &velocity);
  Gas_Particle(glm::vec2 position, glm::vec2 velocity);
  Gas_Particle(glm::vec2 &position, glm::vec2 &velocity, float mass);
  Gas_Particle(glm::vec2 position, glm::vec2 velocity, float mass);
  /**
   * Draw particle to screen
   */
  void draw();
  /**
   * Move particle by amount specified by velocity vector
   */
  void Move();
  /**
   * Flip x component of velocity vector using appropriate vector-matrix multiplication
   */
  void ReverseXDirection();
  /**
   * Flip y component of velocity vector using appropriate vector-matrix multiplication
   */
  void ReverseYDirection();
  /**
   * Apply inelastic collision equation to change velocity and position vectors
   * @param other_velo colliding partner's velocity vector
   * @param other_pos colliding partner's position vector
   * @param other_mass colliding partner's mass
   */
  void Handle_collision(glm::vec2 &other_velo, glm::vec2 &other_pos, float other_mass);
  /**
   * Increase velocity by 1%
   */
  void IncreaseSpeed();
  /**
   * Decrease velocity by 1%
   */
  void DecreaseSpeed();

  // Getters & Setters
  const glm::vec2 &GetPosition() const;
  const glm::vec2 &GetVelocity() const;
  float GetRadius() const;
  float GetMass() const;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  float mass_ = 1;
  float kRadius = 10;
};

}


#endif //IDEAL_GAS_INCLUDE_GAS_PARTICLE_H_
