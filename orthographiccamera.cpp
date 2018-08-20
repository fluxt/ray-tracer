#include "orthographiccamera.h"

OrthographicCamera::OrthographicCamera(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& vup, int width, int height, float offset)
 : Camera(origin, direction, vup, width, height, offset) {}

ray OrthographicCamera::shoot(const int& x, const int& y) {
  float x_p = static_cast<float>(x-width_/2)+std::uniform_real_distribution<float>(0.0, 1.0)(gen_);
  float y_p = static_cast<float>(height_/2-y)+std::uniform_real_distribution<float>(0.0, 1.0)(gen_);
  glm::vec3 ortho_source = origin_ + w_*offset_*x_p + v_*offset_*y_p;
  return ray(ortho_source, u_);
}
