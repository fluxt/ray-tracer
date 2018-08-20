#include "ray.h"

ray::ray() : origin_(glm::vec3()), direction_(glm::vec3()) {}

ray::ray(const glm::vec3& origin, const glm::vec3& direction)
  : origin_(origin), direction_(direction) {}

glm::vec3 ray::origin() const { return origin_; }

glm::vec3 ray::direction() const { return direction_; }

glm::vec3 ray::point_at_parameter(float t) const {
  return origin_+direction_*t;
}