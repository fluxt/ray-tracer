#include "bvh.h"

#include <algorithm>

BVH::BVH(const std::vector<SceneObject*>& scene_objects) : scene_objects_(scene_objects) {
  build_recursive(0, scene_objects_.size(), 0, 0);
}

inline glm::vec3 BVH::calculate_min(int left, int right) {
  float x, y, z;
  x = scene_objects_[left]->min_corner().x;
  y = scene_objects_[left]->min_corner().y;
  z = scene_objects_[left]->min_corner().z;
  for (int i=left; i<right; i++) {
    x = glm::min(x, scene_objects_[i]->min_corner().x);
    y = glm::min(y, scene_objects_[i]->min_corner().y);
    z = glm::min(z, scene_objects_[i]->min_corner().z);
  }
  return glm::vec3(x, y, z);
}

inline glm::vec3 BVH::calculate_max(int left, int right) {
  float x, y, z;
  x = scene_objects_[left]->max_corner().x;
  y = scene_objects_[left]->max_corner().y;
  z = scene_objects_[left]->max_corner().z;
  for (int i=left; i<right; i++) {
    x = glm::max(x, scene_objects_[i]->max_corner().x);
    y = glm::max(y, scene_objects_[i]->max_corner().y);
    z = glm::max(z, scene_objects_[i]->max_corner().z);
  }
  return glm::vec3(x, y, z);
}

inline static bool compare_x(SceneObject* a, SceneObject* b) {
  return a->centroid().x < b->centroid().x;
}

inline static bool compare_y(SceneObject* a, SceneObject* b) {
  return a->centroid().y < b->centroid().y;
}

inline static bool compare_z(SceneObject* a, SceneObject* b) {
  return a->centroid().z < b->centroid().z;
}

void BVH::build_recursive(int left, int right, int index, int depth) {
  nodes.resize(nodes.size()+1);
  nodes[index].min_corner = calculate_min(left, right);
  nodes[index].max_corner = calculate_max(left, right);
  if (right-left <= THRESHOLD) {
    nodes[index].leaf = true;
    nodes[index].index = left;
    nodes[index].size = right-left;
    return;
  }
  int middle = (left+right)/2+(left+right)%2;
  switch (depth%3) {
    case 0:
      std::nth_element(scene_objects_.begin()+left, scene_objects_.begin()+middle, scene_objects_.begin()+right, compare_x);
      break;
    case 1:
      std::nth_element(scene_objects_.begin()+left, scene_objects_.begin()+middle, scene_objects_.begin()+right, compare_y);
      break;
    case 2:
      std::nth_element(scene_objects_.begin()+left, scene_objects_.begin()+middle, scene_objects_.begin()+right, compare_z);
      break;
  }
  nodes[index].leaf = false;
  build_recursive(left, middle, index+1, depth+1);
  nodes[index].index = nodes.size();
  build_recursive(middle, right, nodes.size(), depth+1);
}

inline static bool intersect_box_with_ray(glm::vec3 min_corner, glm::vec3 max_corner, ray r) {
  glm::vec3 origin = r.origin();
  glm::vec3 direction = r.direction();

  // NOT MY CODE https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

  float tmin = (min_corner.x - origin.x) / direction.x;
  float tmax = (max_corner.x - origin.x) / direction.x;

  if (tmin > tmax) std::swap(tmin, tmax);

  float tymin = (min_corner.y - origin.y) / direction.y;
  float tymax = (max_corner.y - origin.y) / direction.y;

  if (tymin > tymax) std::swap(tymin, tymax);

  float tzmin = (min_corner.z - origin.z) / direction.z;
  float tzmax = (max_corner.z - origin.z) / direction.z;

  if (tzmin > tzmax) std::swap(tzmin, tzmax);

  if ((tmin > tymax) || (tymin > tmax))
    return false;

  tmin = std::min(tmin, tymin);
  tmax = std::max(tmax, tymax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return false;

  tmin = std::min(tmin, tzmin);
  tmax = std::max(tmax, tzmax);

  return true;
}

bool BVH::hit(const ray& r, Intersection& intersect) {
  return hit_recursive(0, r, intersect);
}

bool BVH::hit_recursive(int node_index, const ray& r, Intersection& intersect) {
  // case no hit
  if (!intersect_box_with_ray(nodes[node_index].min_corner, nodes[node_index].max_corner, r)) return false;

  // case leaf node
  if (nodes[node_index].leaf == true) {
    // iterate through index, size to find hits
    Intersection new_intersection;
    bool is_hit = false;
    for (int i=nodes[node_index].index; i<nodes[node_index].index+nodes[node_index].size; i++) {
      if (scene_objects_[i]->hit(r, new_intersection)) {
        is_hit = true;
        if (glm::distance(r.origin(), new_intersection.position) < glm::distance(r.origin(), intersect.position)) {
          intersect = new_intersection;
        }
      }
    }
    return is_hit;
  }
  // case internal node
  // left
  bool left_hit = hit_recursive(node_index+1, r, intersect);
  // right
  bool right_hit = hit_recursive(nodes[node_index].index, r, intersect);
  return (left_hit || right_hit);
}