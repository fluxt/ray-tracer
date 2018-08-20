#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "camera.h"

#include <glm/glm.hpp>
#include "ray.h"
#include <random>

class OrthographicCamera : public Camera {
public:
  OrthographicCamera(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& vup, int width, int height, float offset);
  ray shoot(const int& x, const int& y);
};

#endif