/*                              MSCV 2018/2020 SOFTWARE ENGINEERING PROJECT
 *
 * Copyright (C) 2018   Macaulay SADIQ
 *                      Abdul SALAM RASMI
 *                      Deogratias LUKAMBA NSADISA
 *
 * Objective:
 *      Rendering and Implementation of the Harris cornner(points) on 3D point Mesh
 *
 * Development:
 *      The code is developed and implemented on the C++ Qt5 IDE and the
 *      Project file was configured with the GLUT and OpenGL libraries.
 *
 * References:
 *      online source 'http://rodolphe-vaillant.fr,
 *      https://users.dcc.uchile.cl/~isipiran/harris3D.html
 *
 * Notice:
 *      cue was taking for the development of this project from the online sources
 *      stated which was originally developed in #C
 */


#include "vertex.h"
#include <iostream>

using namespace std;



Vertex::Vertex(){
    x = 0;
    y = 0;
    z = 0;
    ring_size = 2;
}


Vertex::~Vertex(){}



void Vertex::getAdjVertices(Mesh m,int c, vector<int> adj_vert){
    set<int>temp;

    for(int j=0; j<m.getNumFace(); j++){
        if(c == m.faces[j].getX()){
            temp.insert(m.faces[j].getY());
            temp.insert(m.faces[j].getZ());
        }
        else if (c == m.faces[j].getY()) {
            temp.insert(m.faces[j].getX());
            temp.insert(m.faces[j].getZ());
        }
        else if (c == m.faces[j].getZ()){
            temp.insert(m.faces[j].getX());
            temp.insert(m.faces[j].getY());
        }
        copy(temp.begin(), temp.end(), inserter(adj_vert, adj_vert.begin()));
        temp.clear();
    }
}


//computing Neigborhood of vertices and adjacent vertices
void Vertex::Neighborhood(Mesh m, vector<vector<int> > neighbor){

    vector<int>neighborhood;
    set<int>temp2;
    vector<int>temp;
    int a;
    for(short int i=0; i<m.getNumVert(); i++){

        temp.push_back(i);

        for(int j=0; j<ring_size; j++){

            for(int k=0; k<temp.size(); k++){
                a = temp.at(k);
                getAdjVertices(m, a, neighborhood);
            }
            copy(neighborhood.begin(), neighborhood.end(), inserter(temp2, temp2.begin()));
            temp.clear();
            copy(temp2.begin(), temp2.end(), inserter(temp, temp.begin()));
            temp2.clear();
        }

        neighbor.push_back(temp);
    }
}







