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
  void keyDown(ci::app::KeyEvent event) override;


  const double kWindowSize = 875;
  const double kMargin = 100;

 private:
  Gas_container gas_container_;
};

}  // namespace container

}  // namespace idealgas
