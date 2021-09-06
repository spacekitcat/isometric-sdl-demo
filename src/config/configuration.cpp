#include "configuration.hpp"

Configuration::Configuration() {
  _targetFps = 60;
  _isDebugMode = false;
}

Configuration::~Configuration() {}

int Configuration::getTargetFps() { return _targetFps; }

bool Configuration::getIsDebugMode() { return _isDebugMode; }

void Configuration::setIsDebugMode(bool enabled) { _isDebugMode = enabled; }