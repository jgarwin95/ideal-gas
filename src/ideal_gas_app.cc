#include <ideal_gas_app.h>

namespace idealgas {

namespace container {

IdealGasApp::IdealGasApp()
    : gas_container_(glm::vec2(kMargin, kMargin), kWindowSize - 2 * kMargin) {

  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::setup() {
  // start the timer
  start_timer_ = std::chrono::system_clock::now();
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  gas_container_.Draw();
}

void IdealGasApp::update() {
  gas_container_.Update();

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
        std::cout << "particle is generated!" << std::endl;
        gas_container_.Generate_particle();
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

  }
}

}  // namespace container

}  // namespace idealgas
