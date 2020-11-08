#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "gas_histogram.h"

namespace idealgas {

namespace container {

/**
 * Simulation of ideal gases.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;
  void setup() override;
  void keyDown(ci::app::KeyEvent event) override;


  const double kWindowSizeX = 1100;
  const double kWindowSizeY = 950;
  const double kMarginSide = 50;
  const double kMarginTop = 50;

 private:
  Gas_container gas_container_;
  GasHistogram  gas_histogram_red_;
  GasHistogram  gas_histogram_blue_;
  GasHistogram  gas_histogram_green_;

  bool is_timer_enabled_ = false;
  /**
   * Timer variables for limiting the rate of particle generation through user input
   */
  std::chrono::time_point<std::chrono::system_clock> start_timer_, end_timer_;
  /**
   * Current setting of particle type
   */
  bool is_red_particle_;
  bool is_blue_particle_;
  bool is_green_particle_;
};

}  // namespace container

}  // namespace idealgas
