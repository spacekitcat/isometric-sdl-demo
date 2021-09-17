
#pragma once

class CameraTarget {
private:
public:
  virtual ~CameraTarget() {}

  virtual std::pair<float, float> getPosition() = 0;
};