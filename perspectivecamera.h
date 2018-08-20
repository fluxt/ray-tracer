#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera.h"

#include <glm/glm.hpp>
#include "ray.h"
#include <random>

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& vup, int width, int height, float distance, float offset);
  ray shoot(const int& x, const int& y);

private:
  float distance_;
};

#endif