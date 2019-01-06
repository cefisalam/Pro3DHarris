#ifndef VECTOR_H
#define VECTOR_H

typedef float Vec4[4];


void setVector(Vec4 v, float a, float b, float c, float d);
void copyVec(Vec4 v, Vec4 res);
void VecCrossProd(Vec4 v1, Vec4 v2, Vec4 res) ;
void Normalize (Vec4 v);
void SumVec(Vec4 v1, Vec4 v2, Vec4 res);
void vecDiff(Vec4 v1, Vec4 v2, Vec4 res);
void vecMultScalar(float f, Vec4 v, Vec4 res);

#endif // VECTOR_H
