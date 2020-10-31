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
   *                            the sketchpad
   * @param sketchpad_size      the side length of the sketchpad, measured in
   *                            screen pixels
   */
  Gas_container(const glm::vec2& top_left_corner, double container_size);

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;
  void Update();

  void Generate_particle();
  void Generate_particle(int x_loc, int y_loc, int x_vel, int y_vel);
  const std::vector<Gas_Particle>& Get_particles() const;

 private:
  glm::vec2 top_left_corner_;
  double container_size_;
  std::vector<Gas_Particle> particles_;

  ci::Rectf container_rect_;
  bool Check_collision(const Gas_Particle &particle, const Gas_Particle &particle_1);
  bool CheckOppositeDirection(const Gas_Particle &particle_1, const Gas_Particle &particle_2) const;
  bool CheckOppositeDirection(const Gas_Particle &particle, std::string&& direction) const;
};

}  // namespace container

}  // namespace idealgas
