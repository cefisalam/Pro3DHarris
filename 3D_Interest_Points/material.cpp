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
#include "material.h"
#include "vector.h"
#include <cstdlib>


using namespace std;


// function to set the properties for the rendering including color

void materials_set_opengl_state(Materials m)
{
    m.shininess = max(min(m.shininess, 128.f), 0.f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT ,  m.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE ,  m.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  m.specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, m.shininess);
}


