#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <glm/glm.hpp>
#include "ray.h"

struct Intersection {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 color;
};

class SceneObject {
public:
  virtual ~SceneObject() {};
  virtual bool hit(const ray& r, Intersection& intersect) = 0;
  virtual glm::vec3 min_corner() const {return glm::vec3();}
  virtual glm::vec3 max_corner() const {return glm::vec3();}
  virtual glm::vec3 centroid() const {return glm::vec3();}
};

#endif