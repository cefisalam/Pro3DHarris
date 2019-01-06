#ifndef MATERIAL_H
#define MATERIAL_H
#include "vector.h"
#include <GL/glut.h>


typedef struct {
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
    float shininess;
} Materials;

void materials_set_opengl_state(Materials m);

#endif // MATERIAL_H
