#include <ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kWindowSize - 2 * kMargin) {

  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color);

  sketchpad_.Draw();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE: {
      break;
    }

    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
