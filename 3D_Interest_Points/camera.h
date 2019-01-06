#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"


typedef struct {
    Vec4 O, X, Y, Z;
} Camera;

Camera camera_init(Vec4 eye, Vec4 up, Vec4 target);
void camera_place(Camera c);
void camera_get_eye   (Camera c, Vec4 res_eye   );
void camera_get_up    (Camera c, Vec4 res_up    );
void camera_get_target(Camera c, Vec4 res_target);
Camera camera_walksideway(Camera c, float step);
Camera camera_walk(Camera c, float step);
Camera camera_pitch(Camera c, float step);
Camera camera_yaw(Camera c, float step);

#endif // CAMERA_H
