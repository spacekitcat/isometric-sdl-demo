
#pragma once

class GameObject {
private:
public:
  virtual ~GameObject() {}

  virtual std::pair<float, float> getPosition() = 0;
};