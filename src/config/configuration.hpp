
#pragma once

#include <iostream>
#include <math.h>

class Configuration {
private:
  int _targetFps;
  bool _isDebugMode;
  std::pair<float, float> _sectorDimensions;
  std::pair<float, float> _tileDimensions;
  std::pair<int, int> _windowDimensions;

public:
  Configuration();
  ~Configuration();

  int getTargetFps();
  bool getIsDebugMode();
  void setIsDebugMode(bool enabled);

  void setSectorDimensions(std::pair<float, float> sectorDimensions);
  std::pair<float, float> getSectorDimensions();

  void setTileDimensions(std::pair<float, float> tileDimensions);
  std::pair<float, float> getTileDimensions();

  void setWindowDimensions(std::pair<int, int> windowDimensions);
  std::pair<int, int> getWindowDimensions();
};