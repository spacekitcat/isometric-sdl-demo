#ifndef SDL2APPLICATION4_INTERSECT_TARGET_HPP
#define SDL2APPLICATION4_INTERSECT_TARGET_HPP

class IntersectTarget {
  public:
    virtual std::pair<float, float> getDimensions() = 0;
};

#endif //SDL2APPLICATION4_INTERSECT_TARGET_HPP
