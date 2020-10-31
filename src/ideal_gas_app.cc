#include <ideal_gas_app.h>

namespace idealgas {

namespace container {

IdealGasApp::IdealGasApp()
    : gas_container_(glm::vec2(kMargin, kMargin), kWindowSize - 2 * kMargin) {

  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  gas_container_.Draw();
}

void IdealGasApp::update() {
  gas_container_.Update();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE: {
      gas_container_.Generate_particle();
    }

    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace container

}  // namespace idealgas
