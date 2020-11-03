#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"

namespace idealgas {

namespace container {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class Gas_container {
 public:
  /**
   * Creates a sketchpad.
   * (Note that sketchpad pixels are larger than screen pixels.)
   *
   * @param top_left_corner     the screen coordinates of the top left corner of
   *                            the container
   * @param container_size      the side length of the container, measured in
   *                            screen pixels
   */
  Gas_container(const glm::vec2& top_left_corner, double container_size);

  /**
   * Draws the border of the container along with all particles
   */
  void Draw() const;
  /**
   * Updates the state of the particles (i.e. movement and collisions)
   */
  void Update();

  /**
   * Generates particle at location 25,25 with a velocity vector of 3,-1.5
   */
  void Generate_particle();
  /**
   * Generates particle with user define location and velocity
   * @param x_loc x location of center of particle
   * @param y_loc y location of center of particle
   * @param x_vel x component of velocity vector
   * @param y_vel y component of velocity vector
   */
  void Generate_particle(int x_loc, int y_loc, int x_vel, int y_vel);
  /**
   * Get current list of particles in container
   * @return vector of Gas_Particles
   */
  const std::vector<Gas_Particle>& Get_particles() const;
  /**
   * Clear vector of particles
   */
  void Clear();
  /**
   * Increase the speed of all particle
   */
  void IncreaseParticleSpeed();
  /**
   * Decrease the speed of all particles
   */
  void DecreaseParticleSpeed();

 private:
  glm::vec2 top_left_corner_;
  double container_size_;
  /**
   * Vector of current particles
   */
  std::vector<Gas_Particle> particles_;
  /**
   * Border of the container
   */
  ci::Rectf container_rect_;
  /**
   * Checks to see if two particles have collided (the distance between their centers is less of the sum
   * of the individual radii)
   * @param particle_1 first particle being compared
   * @param particle_2 second particle being compared
   * @return boolean value denoting if the particles have collided
   */
  bool Check_collision(const Gas_Particle &particle_1, const Gas_Particle &particle_2);
  /**
   * Check if two particles were traveling in the opposite direction. This is a valid collision requirement and
   * will reduce particle sticking
   * @param particle_1 first particle being compared
   * @param particle_2 second particle being compared
   * @return boolean value if the particles were traveling in opposite directions
   */
  bool CheckOppositeDirection(const Gas_Particle &particle_1, const Gas_Particle &particle_2) const;
  /**
   * Check if a particle and wall were traveling in the opposite direction. This is a valid collision requirement and
   * will reduce particles sticking to walls
   * @param particle particle to be compared with
   * @param direction rvalue std::string flag denoting "right", "left", "top", or "bottom" for the wall to be compared against
   * @return boolean value if the particle and wall were "traveling" in opposite directions
   */
  bool CheckOppositeDirection(const Gas_Particle &particle, std::string&& direction) const;
  /**
   * Alter the velocity/direction vector for colliding particles
   * @param particle_1 first particle in collision
   * @param particle_2 second particle in collision
   */
  void HandleCollision(Gas_Particle &particle_1, Gas_Particle &particle_2);
};

}  // namespace container

}  // namespace idealgas
