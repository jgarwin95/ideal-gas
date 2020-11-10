#include <ideal_gas_app.h>

namespace idealgas {

namespace container {

IdealGasApp::IdealGasApp()
    : gas_container_(glm::vec2(kMarginTop, kMarginSide), kWindowSizeX*(1.0/2)),
      gas_histogram_red_(glm::vec2(0, kWindowSizeY - kMarginTop), "red"),
      gas_histogram_blue_(gas_histogram_red_.GetBorder().getUpperRight(), "blue"),
      gas_histogram_green_(gas_histogram_blue_.GetBorder().getUpperRight(), "green"),
      is_red_particle_(true), is_blue_particle_(false), is_green_particle_(false){

  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void IdealGasApp::setup() {
  // start the timer
  start_timer_ = std::chrono::system_clock::now();
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  gas_container_.Draw();
  gas_histogram_red_.Display();
  gas_histogram_blue_.Display();
  gas_histogram_green_.Display();
}

void IdealGasApp::update() {
  // Update gas container
  gas_container_.Update();
  // Ascertain max velocity
  double max_speed = gas_container_.GetMaxSpeed();

  if (!gas_container_.GetRedParticles().empty()) {
    gas_histogram_red_.Update(gas_container_.GetRedParticles(), max_speed);
  }
  if (!gas_container_.GetBlueParticles().empty()) {
    gas_histogram_blue_.Update(gas_container_.GetBlueParticles(), max_speed);
  }
  if (!gas_container_.GetGreenParticles().empty()) {
    gas_histogram_green_.Update(gas_container_.GetGreenParticles(), max_speed);
  }

  // keep refreshing end timer with each loop
  end_timer_ = std::chrono::system_clock::now();
  // calculate the distance in time betwen start and end
  std::chrono::duration<double> elapsed_seconds = end_timer_ - start_timer_;
  // if timer has been enabled by space bar press and elapsed time is more than .5 reset timer and start_timer_
  if ((elapsed_seconds.count() > 0.5) && (is_timer_enabled_)) {
    is_timer_enabled_ = false;
  }
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE: {
      if (!is_timer_enabled_) {
        if (is_red_particle_) {
          gas_container_.Generate_particle("red");
        } else if (is_blue_particle_) {
          gas_container_.Generate_particle("blue");
        } else if (is_green_particle_) {
          gas_container_.Generate_particle("green");
        }
        // start timer
        is_timer_enabled_ = true;
        start_timer_ = std::chrono::system_clock::now();
      }
      break;
    }

    case ci::app::KeyEvent::KEY_DELETE: {
      gas_container_.Clear();
      break;
    }

    case ci::app::KeyEvent::KEY_RIGHT: {
      gas_container_.IncreaseParticleSpeed();
      break;
    }

    case ci::app::KeyEvent::KEY_LEFT: {
      gas_container_.DecreaseParticleSpeed();
      break;
    }

    case ci::app::KeyEvent::KEY_r: {
      is_red_particle_ = true;
      is_blue_particle_ = false;
      is_green_particle_ = false;
      break;
    }

    case ci::app::KeyEvent::KEY_b: {
      is_blue_particle_ = true;
      is_red_particle_ = false;
      is_green_particle_ = false;
      break;
    }

    case ci::app::KeyEvent::KEY_g: {
      is_green_particle_ = true;
      is_red_particle_ = false;
      is_blue_particle_ = false;
      break;
    }

  }
}

}  // namespace container

}  // namespace idealgas
