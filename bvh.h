#ifndef BVH_H
#define BVH_H

#include <glm/glm.hpp>
#include "ray.h"
#include "sceneobject.h"
#include <vector>

#define THRESHOLD 16

class BVH : public SceneObject {
public:
  BVH(const std::vector<SceneObject*>& scene_objects);
  bool hit(const ray& r, Intersection& intersect);

protected:
  struct Node {
      bool leaf;
      glm::vec3 min_corner, max_corner;
      int index, size;
  };

  inline glm::vec3 calculate_min(int left, int right);
  inline glm::vec3 calculate_max(int left, int right);
  void build_recursive(int left, int right, int index, int depth);
  bool hit_recursive(int node_index, const ray& r, Intersection& intersect);

  std::vector<Node> nodes;
  std::vector<SceneObject*> scene_objects_;
};

#endif