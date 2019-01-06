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


#include "vector.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

/* Here are basic functions to calculate vector data of the mesh*/

void setVector(Vec4 v, float idx1, float idx2, float idx3, float idx4){
    v[0] = idx1;
    v[1] = idx2;
    v[2] = idx3;
    v[3] = idx4;
}

void copyVec(Vec4 ip_vec, Vec4 op_vec){
    for (short int i=0; i<4; i++){
        op_vec[i] = ip_vec[i];
    }
}

void VecCrossProd(Vec4 v1, Vec4 v2, Vec4 res){
    res[0] = v1[1]*v2[2] - v1[2]*v2[1];
    res[1] = v1[2]*v2[0] - v1[0]*v2[2];
    res[2] = v1[0]*v2[1] - v1[1]*v2[0];
    res[3] = 0.0;
}


void Normalize(Vec4 v){
    float norm = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if(norm > 0.0001f)
    {
        v[0] /= norm;
        v[1] /= norm;
        v[2] /= norm;
    }
}


void SumVec(Vec4 v1, Vec4 v2, Vec4 res){
    res[0] = v1[0]+v2[0];
    res[1] = v1[1]+v2[1];
    res[2] = v1[2]+v2[2];
    res[3] = v1[3];
}

void vecDiff(Vec4 v1, Vec4 v2, Vec4 res){
    res[0] = v1[0]-v2[0];
    res[1] = v1[1]-v2[1];
    res[2] = v1[2]-v2[2];
    res[3] = 0.0;
}

void vecMultScalar(float f, Vec4 v, Vec4 res){
    res[0] = f*v[0];
    res[1] = f*v[1];
    res[2] = f*v[2];
    res[3] = v[3];
}





