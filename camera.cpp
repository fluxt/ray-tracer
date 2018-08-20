#include "camera.h"

Camera::Camera(const glm::vec3& origin, const glm::vec3& direction, const glm::vec3& vup, int width, int height, float offset)
  : origin_(origin), width_(width), height_(height), offset_(offset), gen_(std::random_device() ()) {
  u_ = glm::normalize(direction);
  v_ = glm::normalize(vup);
  w_ = glm::normalize(glm::cross(u_, v_));
}
