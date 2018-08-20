#include "meshparser.h"

MeshParser::MeshParser(string filename) {
    ifstream infile(filename);
    for (string line; getline(infile, line);) {
        istringstream iss(line);
        string type;
        iss >> type;
        if (type == "v") {
            glm::vec3 v;
            iss >> v.x;
            iss >> v.y;
            iss >> v.z;
            vertices.push_back(v);
        } else if (type == "f") {
            int f[3];
            iss >> f[0] >> f[1] >> f[2];
            triangles.push_back(new Triangle(vertices[f[0]-1], vertices[f[1]-1], vertices[f[2]-1], glm::vec3(0.36, 1.0, 0.455)));
        }
    }
}


MeshParser::~MeshParser() {
    for (unsigned i=0; i<triangles.size(); i++) {
        delete triangles[i];
    }
    triangles.clear();
}