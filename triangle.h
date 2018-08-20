#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include "ray.h"
#include "sceneobject.h"

class Triangle : public SceneObject {
public:
  Triangle(const glm::vec3& vert1, const glm::vec3& vert2, const glm::vec3& vert3, const glm::vec3& color);
  bool hit(const ray& r, Intersection& intersect);
  glm::vec3 max_corner() const;
  glm::vec3 min_corner() const;
  glm::vec3 centroid() const;

protected:
  glm::vec3 vert1_, vert2_, vert3_;
  glm::vec3 color_;
};

#endif