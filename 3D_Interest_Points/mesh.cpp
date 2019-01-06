    /*                              MSCV 2018/2020 SOFTWARE ENGINEERING PROJECT
 *
 * Copyright (C) 2018   Macaulay SADIQ
 *                      Abdul SALAM RASMI
 *                      Deogratias LUKAMBA NSADISA
 *
 * Objective;
 *      Rendering and Implementation of the Harris cornner(points) on 3D point Mesh
 *
 * Development:
 *      The code is developed and implemented on the C++ Qt5 IDE and the
 *      Project file was configured with the GLUT and OpenGL libraries.
 *
 * References:
 *      online source 'http://rodolphe-vaillant.fr
 *      https://users.dcc.uchile.cl/~isipiran/harris3D.html
 *
 * Notice:
 *      cue was taking for the development of this project from the online sources
 *      stated which was originally developed in #C
 */


#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#include "mesh.h"
#include "material.h"


using namespace std;

Mesh::Mesh()
{
    nb_faces = 0;
    nb_vertices = 0;
    nb_edges = 0;
    x = 0;
    y = 0;
    z = 0;
}

Mesh::Mesh(const string off_file){

ReadFile(off_file);

}

Mesh::Mesh(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}

Mesh::~Mesh(){}

// test function to display class vectors for checks

ostream& operator<<(ostream& ost, Mesh vertex){
    ost <<vertex.getX()<<", " <<vertex.getY()<< ", " <<vertex.getZ();
    return ost;
}


// Function for reading and storing the data of the Mesh

void Mesh::ReadFile(const string off_file){
    string first_line;
    string line;
    ifstream file(off_file);

    if(file.good()){
        getline(file,  first_line);

// Check file formatart
        if(first_line != "OFF"){
            cout<<"INVALIDE FILE FORMAT !!!"<<endl;
            cout<< "Only .off file format is required."<<endl;
            file.close();
            exit(EXIT_FAILURE) ;
        }

        else{

            cout<<"File path:- "<<off_file<<endl<<endl;

// Reading file sumary and storing the data

            file>>nb_vertices>>nb_faces>>nb_edges;
            cout<< "Number of vertices is: "<<nb_vertices<<endl;
            cout << "Number of faces is: "<< nb_faces<<endl;
            cout << "Number of edges is: "<< nb_edges<<endl<<endl;

// Storing the vertex data in vector class 'points'

            for(int i=0; i<nb_vertices; i++){
                getline(file,  line);
                float X,Y,Z;
                file>>X>>Y>>Z;
                points.push_back({X,Y,Z});
            }

// Storing Face data in vector class 'faces'

            for(int i=0; i<nb_faces; i++){
                getline(file, line);
                unsigned int numVert;
                file>>numVert;
                assert(numVert == 3);
                float f1,f2,f3;
                file>>f1>>f2>>f3;
                faces.push_back({f1,f2,f3});
            }

// Computing the normals of the data

            float vec[3] = {0,0,0};
            float vrt[3] = {0,0,0};
            float vec_diff1[3]; float v_prod[3]; float vec_diff[3];
            Mesh *v0, *v1, *v2 = NULL;
            for(short int i=0; i<nb_vertices *3; i++){
                meshnormls.push_back(0.0);
            }

            vector<float>scaled_val;
            for(int i=0; i<3; i++){
                scaled_val.push_back(0.0);
            }

            for(vector<Mesh>::iterator itr = points.begin(); itr != points.end(); ++itr){

                for(int i=0; i<3; i++)
                {
                    if (i == 0)
                        v_max = max((*itr).x, v_max);
                    else if (i == 1)
                        v_max = max((*itr).y, v_max);
                    else if (i == 2)
                        v_max = max((*itr).z, v_max);

                }
            }

        // Computing the scaled vertices data

            for(vector<Mesh>::iterator itr = points.begin(); itr != points.end(); ++itr){

                vec[0] = (*itr).x + vec[0];
                vec[1] = (*itr).y + vec[1];
                vec[2] = (*itr).z + vec[2];
            }
            vec[0] = vec[0] / nb_vertices;
            vec[1] = vec[1] / nb_vertices;
            vec[2] = vec[2] / nb_vertices;

            for(vector<Mesh>::iterator itr = points.begin(); itr != points.end(); ++itr){

                vrt[0] = (*itr).x - vec[0];
                vrt[1] = (*itr).y - vec[1];
                vrt[2] = (*itr).z - vec[2];

                vrt[0] = vrt[0] / v_max;
                vrt[1] = vrt[1] / v_max;
                vrt[2] = vrt[2] / v_max;

                scaled_vert.push_back({vrt[0],vrt[1],vrt[2]});
            }

// computing the Meshnormals and storing in vector 'meshnormls'

            for(vector<Mesh>::iterator itr = faces.begin(); itr != faces.end(); ++itr){

                unsigned int a = (*itr).x;
                unsigned int b = (*itr).y;
                unsigned int c = (*itr).z;

                v0 = &scaled_vert.at(a);
                v1 = &scaled_vert.at(b);
                v2 = &scaled_vert.at(c);

                //vertex difference

                vec_diff[0] = (*v1).x - (*v0).x;
                vec_diff[1] = (*v1).y - (*v0).y;
                vec_diff[2] = (*v1).z - (*v0).z;

                vec_diff1[0] = (*v2).x - (*v0).x;
                vec_diff1[1] = (*v2).y - (*v0).y;
                vec_diff1[2] = (*v2).z - (*v0).z;

                // crossproduct of vertices

                v_prod[0] = (vec_diff[1] * vec_diff1[2]) - (vec_diff[2] * vec_diff1[1]);
                v_prod[1] = (vec_diff[2] * vec_diff1[0]) - (vec_diff[0] * vec_diff1[2]);
                v_prod[2] = (vec_diff[0] * vec_diff1[1]) - (vec_diff[1] * vec_diff1[0]);

                //normalizing the cross product

                float norm = sqrt(v_prod[0] * v_prod[0]) + (v_prod[1] * v_prod[1]) + (v_prod[2] * v_prod[2]);

                if(norm > 0.0001){
                    v_prod[0] /= norm;
                    v_prod[1] /= norm;
                    v_prod[2] /= norm;
                }

                for(short int n=0; n<3; n++){
                    meshnormls.at(a *3+n) += v_prod[n];
                    meshnormls.at(b *3+n) += v_prod[n];
                    meshnormls.at(c *3+n) += v_prod[n];
                }
            }

            for(short int i=0; i<nb_vertices; i++){
                float vec[3] = {meshnormls.at(i*3), meshnormls.at(i*3+1), meshnormls.at(i*3+2)};
                float norm = sqrt((vec[0] * vec[0]) + (vec[1] *vec[1]) + (vec[2] * vec[2]));
                if(norm > 0.0001){
                    vec[0] /= norm;
                    vec[1] /= norm;
                    vec[2] /= norm;
                }
                meshnormls.at(i*3) = vec[0];
                meshnormls.at(i*3+1) = vec[1];
                meshnormls.at(i*3+2) = vec[2];
            }
        }
    }

    else {
        cout<<"FILE ERROR !!!"<<endl;
        exit(EXIT_FAILURE);
    }
}



/* Drawing the Mesh from the computed data using OpenGl */


void Mesh::DrawMesh() {

    vector<float>verts;
    vector<int>index;

    for(vector<Mesh>::iterator i=scaled_vert.begin(); i!=scaled_vert.end(); ++i){
        verts.push_back((*i).x);
        verts.push_back((*i).y);
        verts.push_back((*i).z);
    }
    for(vector<Mesh>::iterator i=faces.begin(); i!=faces.end(); ++i){
        index.push_back((*i).x);
        index.push_back((*i).y);
        index.push_back((*i).z);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &verts[0]);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &meshnormls[0]);

    glDrawElements(GL_TRIANGLES, nb_faces*3, GL_UNSIGNED_INT, &index[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}

/* Drawing and Highlighting the normals of the Mesh*/

void Mesh::DrawVertices(){
    GLboolean s;
    glGetBooleanv(GL_LIGHTING, &s);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.1);
    glPointSize(5.0);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);

    for( short int i = 0; i < nb_vertices; i++) {

        glVertex3f(scaled_vert[i].x, scaled_vert[i].y, scaled_vert[i].z);
    }
    glEnd();
    if(s) glEnable(GL_LIGHTING);
}





