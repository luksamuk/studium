#ifndef STMATH_H
#define STMATH_H

#include <math.h>

/* 2D Vector */
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



/* 3D Vector */
typedef struct {
    float x, y, z;
} st_vec3;

// Vector arithmetic
st_vec3 st_vec3_sum(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_sub(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_neg(st_vec3 a);
st_vec3 st_vec3_cross(st_vec3 a, st_vec3 b);

// Scalar operations
float   st_vec3_sqdist(st_vec3 a, st_vec3 b);
float   st_vec3_sqlen(st_vec3 a);
float   st_vec3_dot(st_vec3 a, st_vec3 b);



/* 2D Matrix */
typedef struct {
    union {
	float A[4];
	struct {
	    float a11, a12,
		a21, a22,
		a31, a32;
	};
    };
} st_mat2;

// TODO



/* 3D Matrix */
typedef struct {
    union {
	float A[9];
	struct {
	    float a11, a12, a13,
		a21, a22, a23,
		a31, a32, a33;
	};
    };
} st_mat3;

// Matrix operations
st_mat3 st_mat3_identity();
st_mat3 st_mat3_transpose(const st_mat3* a);
st_mat3 st_mat3_sum(const st_mat3* a, const st_mat3* b);
st_mat3 st_mat3_sub(const st_mat3* a, const st_mat3* b);
/* st_mat3 st_mat3_mult(const st_mat3* a, const st_mat3* b); */ // todo

// Scalar operations
st_mat3 st_mat3_scalar_mult(float c, const st_mat3* a);
float   st_mat3_det(const st_mat3* a);

// Debugging
void    st_mat3_print(const st_mat3* a);



/* 4D Matrix */
typedef struct {
    union {
	float A[16];
	struct {
	    float a11, a12, a13, a14,
		a21, a22, a23, a24,
		a31, a32, a33, a34,
		a41, a42, a43, a44;
	};
    };
} st_mat4;

// Matrix operations
st_mat4 st_mat4_identity();

// Scalar operations
// Debugging
void    st_mat4_print(const st_mat4* a);


/* Determinant predicates */
float   st_orient2d(st_vec2 a, st_vec2 b, st_vec2 c);
// The following require an st_mat4
/* float   st_orient3d(st_vec3 a, st_vec3 b, st_vec3 c); */
/* float   st_incircle2d(st_vec2 a, st_vec2 b, st_vec2 c, st_vec2 d); */

#endif // STMATH_H
