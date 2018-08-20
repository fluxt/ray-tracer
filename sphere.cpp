#include "sphere.h"
#include <glm/gtx/intersect.hpp>

Sphere::Sphere(const glm::vec3& origin, const float& radius, const glm::vec3& color) : origin_(origin), radius_(radius), color_(color) {}

bool Sphere::hit(const ray& r, Intersection& intersect) {
  bool ret = glm::intersectRaySphere(r.origin(), r.direction(), origin_, radius_, intersect.position, intersect.normal);
  if (ret == true) {
    intersect.color = color_;
  }
  return ret;
}

glm::vec3 Sphere::min_corner() const {
  return origin_-radius_;
}

glm::vec3 Sphere::max_corner() const {
  return origin_+radius_;
}

glm::vec3 Sphere::centroid() const {
  return origin_;
}
