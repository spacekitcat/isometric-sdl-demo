#ifndef SDL2APPLICATION4_CAMERA_HPP
#define SDL2APPLICATION4_CAMERA_HPP

#include <iostream>

class Camera {
private:
  std::pair<float, float> _position;

public:
  std::pair<float, float> getPosition();

  void applyDelta(std::pair<float, float> delta);
};


#endif //SDL2APPLICATION4_CAMERA_HPP
