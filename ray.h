#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>

class ray {
public:
  ray();
  ray(const glm::vec3& origin, const glm::vec3& direction);

  glm::vec3 origin() const;
  glm::vec3 direction() const;
  glm::vec3 point_at_parameter(float t) const;

private:
  glm::vec3 origin_;
  glm::vec3 direction_;
};

#endif