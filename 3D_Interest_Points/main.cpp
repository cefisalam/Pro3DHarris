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


#include <QCoreApplication>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdbool>
#include <cmath>

#include "mesh.h"
#include "vector.h"
#include "material.h"
#include "camera.h"
#include "vertex.h"

using namespace std;


// Initialization of the Graphic interface

static int _windowNumber;
int _angle  = 0;

bool _anim   = true;
bool _ortho  = false;
bool _normal = false;


float _width  = 800;
float _height = 600;

// Instances to call funtion for the rendering
Camera _cam;
Mesh _mesh;

// initialization for the colour texture... for 3D model
Materials metal = {
    {0.5, 0.5, 0.5, 0.5},
    {0.5, 0.5, 0.5, 0.5},
    {0.5, 0.5, 0.5, 0.5},
    200.f
};



GLfloat viewangle = 180, tippangle = 5;
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;
GLfloat x = 2.5;


// setting the functions of special keys (arrow keys) for required controls

void Special_Keys (int key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT :  _cam = camera_walksideway(_cam, -0.1f);  break;
    case GLUT_KEY_RIGHT:  _cam = camera_walksideway(_cam, 0.1f);  break;
    case GLUT_KEY_UP   :  _cam = camera_pitch(_cam,  0.1f); break;
    case GLUT_KEY_DOWN :  _cam = camera_pitch(_cam, -0.1f);  break;

    }

    glutPostRedisplay();
}

// Setting the other keys for rotation and translation of the 3D model

void key(unsigned char c, int mx, int my)
{
    mx = my;
    my = mx;

    static bool depth      = true;
    static bool wire       = true;
    static bool light      = true;
    static bool light0     = true;
    static bool flat_shade = false;

    switch (c)
    {

    case'a':    _anim = !_anim;     break;
    case'p':    _normal = !_normal; break;
    case 'l' : viewangle -= 5;  break;
    case 'j' : viewangle += 5;  break;
    case 'o': _cam = camera_walk(_cam, -0.1f); break;
    case 'i': _cam = camera_walk(_cam, +0.1f); break;
    case'w':
        if(wire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wire = !wire;
        break;
    case'0':
        if(light0) glEnable(GL_LIGHT0);
        else      glDisable(GL_LIGHT0);
        light0 = !light0;
        break;

    case 27 :
        glFinish();
        glutDestroyWindow(_windowNumber);
        exit (0);
        break;
    }
    glutPostRedisplay();
}

void no_events()
{
    _angle = _angle+1 % 360;
    glutPostRedisplay();
}

void reshape(int x, int y)
{
    glViewport(0, 0, x, y);
    _width  = x;glRotatef(_angle, 0.f, 1.f, 0.f);
    _height = y;
}


// Setting the light on the model

void init_light()
{

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    int max_light;
    glGetIntegerv(GL_MAX_LIGHTS, &max_light);

    Vec4 light0Ambient, light0Diffuse, light0Specular;
    setVector(light0Ambient , 0.2f, 0.2f, 0.2f, 0.f);
    setVector(light0Diffuse , 1.0f, 1.0f, 1.0f, 0.f);
    setVector(light0Specular, 1.0f, 1.0f, 1.0f, 0.f);
    int i = 0;
    for(i = 0; i < 3; i++)
    {
        glLightfv(GL_LIGHT0+i, GL_AMBIENT , light0Ambient);
        glLightfv(GL_LIGHT0+i, GL_DIFFUSE , light0Diffuse);
        glLightfv(GL_LIGHT0+i, GL_SPECULAR, light0Specular);
    }

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100);
}

void set_torch()
{
    Vec4 light2_position;
    setVector(light2_position, 0.f, 0.f, 0.f, 1.f);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    setVector(light2_position, 0.0f, 0.0f, -1.0f, 0.f);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_position);
}

// set light position

void set_light_positions()
{
    Vec4 light0_position;
    setVector(light0_position, -3.f, 1.f, 0.f, 1.f);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    Vec4 light1_position;
    setVector(light1_position, 0.f, 2.f, 4.f, 1.f);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
}

// Function the render the 3D model

void display(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(_ortho) glOrtho(-2.f, 2.f, -2.f, 2.f, -2.f, 2.f );
    else       gluPerspective(60.f, _width/_height, 0.1f, 100.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef (tippangle, 1,0,0);
    glRotatef (viewangle, 0,0,1);

    set_torch();
    camera_place(_cam);
    set_light_positions();
    materials_set_opengl_state(metal);

    glPushMatrix();
    if(_anim){
        glRotatef(_angle, 10.0, 0.0, 0.0);
    }else
        glTranslatef(0.f, 0.10f, 0.f );
    glScalef(x,x,x);

    _mesh.DrawMesh();
    if(_normal) _mesh.DrawVertices();
    glPopMatrix();

    // Window refresh
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    _mesh.ReadFile("/home/sadiq/Desktop/seashell.off"); // .off file to be rendered

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // initializing the glut gui window
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(240, 212);
    _windowNumber = glutCreateWindow("3D RENDERING");

    // calling keyboard and special key function
    glutKeyboardFunc(key);
    glutSpecialFunc(Special_Keys);

    // calling the display function
    glutDisplayFunc(display);
    glutIdleFunc(no_events);
    glutReshapeFunc(reshape);

    //initializing opengl rendering features
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glShadeModel(GL_SMOOTH);
    init_light();

    Vec4 eye = {0.f, 0.f, 4.f, 1.f};
    Vec4 up  = {0.f, 1.f, 0.f, 1.f};
    Vec4 aim = {0.f, 0.f, 0.f, 1.f};
    _cam = camera_init(eye, up, aim);

    glutMainLoop();


    return 0;
}
