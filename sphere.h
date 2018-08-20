#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include "ray.h"
#include "sceneobject.h"

class Sphere : public SceneObject {
public:
  Sphere(const glm::vec3& origin, const float& radius, const glm::vec3& color);
  bool hit(const ray& r, Intersection& intersect);
  glm::vec3 min_corner() const;
  glm::vec3 max_corner() const;
  glm::vec3 centroid() const;

protected:
  float radius_;
  glm::vec3 origin_;
  glm::vec3 color_;
};

#endif