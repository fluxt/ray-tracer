#ifndef MESHPARSER_H
#define MESHPARSER_H

#include <string>
#include <vector>
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

using namespace std;

class MeshParser {
public:
    MeshParser(std::string filename);

    ~MeshParser();

    std::vector<glm::vec3> vertices;
    std::vector<SceneObject*> triangles;
};

#endif