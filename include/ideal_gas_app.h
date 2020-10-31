#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

namespace container {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;
  void setup() override;
  void keyDown(ci::app::KeyEvent event) override;


  const double kWindowSize = 875;
  const double kMargin = 100;

 private:
  Gas_container gas_container_;

  bool is_timer_enabled_ = false;
  std::chrono::time_point<std::chrono::system_clock> start_timer_, end_timer_;

};

}  // namespace container

}  // namespace idealgas
