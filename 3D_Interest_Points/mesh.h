#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <string>
#include <vector>

class Mesh
{
private:

    int nb_vertices;
    int nb_faces;
    int nb_edges;
    float x,y,z;
    float v_max;

public:

    Mesh();
    Mesh(const std::string file);
    Mesh(float, float, float);
    ~Mesh();
    std::vector< Mesh > points;
    std::vector< Mesh > faces;
    void ReadFile(const std::string infile);
    void DrawMesh();
    void DrawVertices();  
    std::vector<Mesh>scaled_vert;
    std::vector<float>meshnormls;
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    int getNumVert(){return nb_vertices;}
    int getNumFace(){return nb_faces;}


};

#endif // MESH_H
