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


#include "camera.h"
#include <GL/glut.h>

// Compute the camera frame according to eye, up and target
Camera camera_init(Vec4 eye, Vec4 up, Vec4 target)
{
    Camera c;

    copyVec( eye, c.O );
    copyVec( up , c.Y );
    Normalize(c.Y);

    vecDiff(target, eye, c.Z);
    Normalize(c.Z);

    VecCrossProd(c.Z, c.Y, c.X);
    Normalize(c.X);

    return c;
}

// Call gluLookAt() with the correct parameters
void camera_place(Camera c)
{
    Vec4 eye, aim, up;
    camera_get_eye(c, eye);
    camera_get_up(c, up);
    camera_get_target(c, aim);

    gluLookAt(eye[0], eye[1], eye[2],
            aim[0], aim[1], aim[2],
            up[0],  up[1],  up[2]
            );
}

void camera_get_eye(Camera c, Vec4 eye)
{
    copyVec(c.O, eye);
}

void camera_get_up(Camera c, Vec4 up)
{
    copyVec(c.Y, up);
}

void camera_get_target(Camera c, Vec4 target)
{
    SumVec(c.O, c.Z, target);
}

// Translate model left and right
Camera camera_walksideway(Camera c, float step)
{
    Vec4 dl;
    vecMultScalar(step, c.X, dl);
    SumVec(c.O, dl, c.O);
    return c;
}

// zooming in/out model 3D
Camera camera_walk(Camera c, float step)
{
    Vec4 dl;
    vecMultScalar(step, c.Z, dl);
    SumVec(c.O, dl, c.O);
    return c;
}

// Rotating the 3D model
Camera camera_pitch(Camera c, float step)
{
    Vec4 dl;
    vecMultScalar(step, c.Y, dl);
    SumVec(c.Z, dl, c.Z);
    Normalize(c.Z);
    VecCrossProd(c.X, c.Z, c.Y);
    Normalize(c.Y);
    return c;
}

// Rotation left and right
Camera camera_yaw(Camera c, float step)
{
    Vec4 dl;
    vecMultScalar(step, c.X, dl);
    SumVec(c.Z, dl, c.Z);
    Normalize(c.Z);
    VecCrossProd(c.Z, c.Y, c.X);
    Normalize(c.X);
    return c;
}
