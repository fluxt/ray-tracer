#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "ray.h"
#include <random>

class Camera {

public:
  Camera(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& vup, int width, int height, float offset);
  virtual ~Camera() {};
  virtual ray shoot(const int& x, const int& y) = 0;

  glm::vec3 origin() const { return origin_; }
  glm::vec3 u() const { return u_; }

protected:
  // u = forwards (aka positive x direction)
  // v = upwards (aka positive y direction)
  // w = rightwards (aka positive z direction)
  glm::vec3 origin_;
  glm::vec3 u_, v_, w_;
  int width_, height_;
  float offset_;

  std::mt19937 gen_;
};

#endif