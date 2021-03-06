//
// Created by garwi on 10/29/2020.
//

#include <ideal_gas_app.h>

using idealgas::container::IdealGasApp;

void prepareSettings(IdealGasApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);

