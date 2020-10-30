#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class Sketchpad {
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
  Sketchpad(const glm::vec2& top_left_corner, double sketchpad_size);

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;

 private:
  glm::vec2 top_left_corner_;

  double sketchpad_size_;

};

}  // namespace visualizer

}  // namespace idealgas
