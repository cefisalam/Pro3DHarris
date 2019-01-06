#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <set>
#include "mesh.h"

class Vertex {

public:
    float x, y, z;
    int ring_size;
    Vertex();
    ~Vertex();
    void Neighborhood(Mesh m, std::vector<std::vector<int> > n);
    void getAdjVertices(Mesh m,int x, std::vector<int> xx);

};

#endif // VERTEX_H
