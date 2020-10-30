#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

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

 private:
  glm::vec2 top_left_corner_;
  double container_size_;

  ci::Rectf container_rect_;
};

}  // namespace visualizer

}  // namespace idealgas