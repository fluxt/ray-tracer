#include "triangle.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/normal.hpp>

Triangle::Triangle(const glm::vec3& vert1, const glm::vec3& vert2, const glm::vec3& vert3, const glm::vec3& color) 
  : vert1_(vert1), vert2_(vert2), vert3_(vert3), color_(color) {}

bool Triangle::hit(const ray& r, Intersection& intersect) {
  glm::vec3 bary_pos;
  bool ret = glm::intersectRayTriangle(r.origin(), r.direction(), vert1_, vert2_, vert3_, bary_pos);
  if (ret == true) {
    glm::vec3 triangle_normal = glm::triangleNormal(vert1_, vert2_, vert3_);

    if (glm::dot(triangle_normal, r.direction())<=0) {
      intersect.normal = triangle_normal;
    } else {
      intersect.normal = -triangle_normal;
    }
    intersect.position = r.origin()+r.direction()*bary_pos[2];
    intersect.color = color_;
  }
  return ret;
}

glm::vec3 Triangle::min_corner() const {
  float x = glm::min(glm::min(vert1_.x, vert2_.x), vert3_.x);
  float y = glm::min(glm::min(vert1_.y, vert2_.y), vert3_.y);
  float z = glm::min(glm::min(vert1_.z, vert2_.z), vert3_.z);
  return glm::vec3(x, y, z);
}

glm::vec3 Triangle::max_corner() const {
  float x = glm::max(glm::max(vert1_.x, vert2_.x), vert3_.x);
  float y = glm::max(glm::max(vert1_.y, vert2_.y), vert3_.y);
  float z = glm::max(glm::max(vert1_.z, vert2_.z), vert3_.z);
  return glm::vec3(x, y, z);
}

glm::vec3 Triangle::centroid() const {
  return (vert1_+vert2_+vert3_)/3.0F;
}

