
#pragma once

class Configuration {
private:
  int _targetFps;
  bool _isDebugMode;

public:
  Configuration();
  ~Configuration();

  int getTargetFps();
  bool getIsDebugMode();
  void setIsDebugMode(bool enabled);
};