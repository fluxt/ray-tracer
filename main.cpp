#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <random>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "include/lodepng/lodepng.h"
#include "sceneobject.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "orthographiccamera.h"
#include "perspectivecamera.h"
#include "bvh.h"
#include "meshparser.h"

using namespace std;

int ray_trace(Camera& camera, SceneObject& scene_object, vector<unsigned char>* image,
              unsigned height, unsigned width, unsigned sampling);

int main(int argc, char *argv[]) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> loc_dis(-0.5, 0.5);
  std::uniform_real_distribution<> color_dis(0.0, 1.0);

  unsigned width = 512, height = 512;
  unsigned sampling = 32;

  std::string modelname = "dragon";

  vector<unsigned char> image;
  image.resize(width * height * 4);

//-------------------------Scene-----------------------------------

  glm::vec3 origin(0.0, 0.0, 0.0);
  glm::vec3 x_dir(1.0, 0.0, 0.0);
  glm::vec3 y_dir(0.0, 1.0, 0.0);
  glm::vec3 z_dir(0.0, 0.0, 1.0);
  glm::vec3 camera_pos(10.0, 10.0, 1.0);
  camera_pos /= 10;
  glm::vec3 look_dir = glm::normalize(origin - camera_pos);
  glm::vec3 vup = glm::cross(glm::cross(look_dir, y_dir), look_dir);

  MeshParser mp("models/"+modelname+".obj");
  BVH bvh(mp.triangles);

  OrthographicCamera cam_ortho(camera_pos, look_dir, vup, width, height, 2.0/height);
  PerspectiveCamera cam_perspec(camera_pos, look_dir, vup, width, height, 1.0, 2.0/height);

//-------------------------BVH Orthographic------------------------

  ray_trace(cam_ortho, bvh, &image, height, width, sampling);
  lodepng::encode(modelname+"-orthographic.png", image, width, height);

//-------------------------BVH Perspective-------------------------

  ray_trace(cam_perspec, bvh, &image, height, width, sampling);
  lodepng::encode(modelname+"-perspective.png", image, width, height);

//-------------------------Cleanup---------------------------------

  return 0;
}

int ray_trace(Camera& camera, SceneObject& scene_object, vector<unsigned char>* image,
              unsigned height, unsigned width, unsigned sampling) {
  if (image == NULL) return -1;

  ray r;
  bool is_hit;
  Intersection intersect;
  glm::vec3 color;
  vector<glm::vec3> colors;
  colors.resize(sampling);

  for(unsigned y = 0; y < height; y++) {
  if (y%32 == 0) cout << y << endl;
  for(unsigned x = 0; x < width; x++) {
    for(unsigned s = 0; s < sampling; s++) {
      r = camera.shoot(x, y);
      glm::vec3 vup = r.origin();
      intersect.position = glm::vec3(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
      is_hit = scene_object.hit(r, intersect);
      if (is_hit) {
        colors[s] = intersect.color * (0.2 + 0.8 * std::abs(glm::dot(glm::normalize(intersect.normal), glm::normalize(camera.u()))));
      } else {
        colors[s] = glm::vec3(0.2, 0.2, 0.2);
      }
    }
    color = glm::vec3(0.0, 0.0, 0.0);
    for(unsigned s = 0; s < sampling; s++) {
      color += colors[s];
    }
    color /= sampling;
    for(unsigned i=0; i<3; i++) {
      (*image)[4 * width * y + 4 * x + i] = static_cast<int>(color[i] * 255.0);
    }
    (*image)[4 * width * y + 4 * x + 3] = 0xFF;
  }}

  return 0;
}

  // unsigned balls_n = 10000;
  // float balls_r = 0.01;
  // scene_objects.resize(balls_n);
  // for (unsigned i=0; i<balls_n; i++) {
  //   scene_objects[i] = new Sphere(glm::vec3(loc_dis(gen), loc_dis(gen), loc_dis(gen)), balls_r, glm::vec3(color_dis(gen), color_dis(gen), color_dis(gen)));
  // }
  // for (unsigned i=0; i<balls_n; i++) {
  //   delete scene_objects[i];
  // }
  // scene_objects.clear();
