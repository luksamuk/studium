#ifndef STMATH_H
#define STMATH_H

#include <math.h>

// 2D Vector
typedef struct {
    float x, y;
} st_vec2;

// Vector arithmetic
st_vec2 st_vec2_sum(st_vec2 a, st_vec2 b);
st_vec2 st_vec2_sub(st_vec2 a, st_vec2 b);
st_vec2 st_vec2_neg(st_vec2 a);

// Scalar operations
float   st_vec2_sqdist(st_vec2 a, st_vec2 b);
float   st_vec2_sqlen(st_vec2 a);
float   st_vec2_dot(st_vec2 a, st_vec2 b);


// 3D Vector
typedef struct {
    float x, y, z;
} st_vec3;

// Vector arithmetic
st_vec3 st_vec3_sum(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_sub(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_neg(st_vec3 a);

// Scalar operations
float   st_vec3_sqdist(st_vec3 a, st_vec3 b);
float   st_vec3_sqlen(st_vec3 a);
float   st_vec3_dot(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_cross(st_vec3 a, st_vec3 b);

#endif // STMATH_H
