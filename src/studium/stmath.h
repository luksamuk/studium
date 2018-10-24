#ifndef STMATH_H
#define STMATH_H

#include <math.h>

/* Global definitions */

#define st_degtorad(d) (M_PI * d) / 180.0
#define st_radtodeg(r) (180.0 * r) / M_PI

/* 2D Vector */
typedef struct {
    float x, y;
} st_vec2;

// Vector arithmetic
st_vec2 st_vec2_zero();
st_vec2 st_vec2_one();
st_vec2 st_vec2_new(const float values[static 2]);
st_vec2 st_vec2_sum(st_vec2 a, st_vec2 b);
st_vec2 st_vec2_sub(st_vec2 a, st_vec2 b);
st_vec2 st_vec2_scalar_mult(float c, st_vec2 a);
st_vec2 st_vec2_neg(st_vec2 a);

// Scalar operations
float   st_vec2_sqdist(st_vec2 a, st_vec2 b);
float   st_vec2_sqlen(st_vec2 a);
float   st_vec2_dot(st_vec2 a, st_vec2 b);

// Debugging
void    st_vec2_print(const st_vec2* a);


/* 3D Vector */
typedef struct {
    float x, y, z;
} st_vec3;

// Vector arithmetic
st_vec3 st_vec3_zero();
st_vec3 st_vec3_one();
st_vec3 st_vec3_new(const float values[static 3]);
st_vec3 st_vec3_sum(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_sub(st_vec3 a, st_vec3 b);
st_vec3 st_vec3_scalar_mult(float c, st_vec3 a);
st_vec3 st_vec3_neg(st_vec3 a);
st_vec3 st_vec3_cross(st_vec3 a, st_vec3 b);

// Scalar operations
float   st_vec3_sqdist(st_vec3 a, st_vec3 b);
float   st_vec3_sqlen(st_vec3 a);
float   st_vec3_dot(st_vec3 a, st_vec3 b);

// Debugging
void    st_vec3_print(const st_vec3* a);


/* 4D Vector */
typedef struct {
    float x, y, z, w;
} st_vec4;

// Vector arithmetic
st_vec4 st_vec4_zero();
st_vec4 st_vec4_one();
st_vec4 st_vec4_new(const float values[static 4]);
st_vec4 st_vec4_sum(st_vec4 a, st_vec4 b);
st_vec4 st_vec4_sub(st_vec4 a, st_vec4 b);
st_vec4 st_vec4_scalar_mult(float c, st_vec4 a);
st_vec4 st_vec4_neg(st_vec4 a);

// Scalar operations
float   st_vec4_sqdist(st_vec4 a, st_vec4 b);
float   st_vec4_sqlen(st_vec4 a);
float   st_vec4_dot(st_vec4 a, st_vec4 b);

// Debugging
void    st_vec4_print(const st_vec4* a);

/* 2D Matrix */
typedef struct {
    union {
	float A[4];
	struct {
	    float a11, a12,
		a21, a22;
	};
    };
} st_mat2;

// Matrix operations
st_mat2 st_mat2_identity();
st_mat2 st_mat2_transpose(const st_mat2* a);
st_mat2 st_mat2_sum(const st_mat2* a, const st_mat2* b);
st_mat2 st_mat2_sub(const st_mat2* a, const st_mat2* b);
st_mat2 st_mat2_mult(const st_mat2* a, const st_mat2* b);
int st_mat2_inverse(st_mat2* dest, const st_mat2* a);

// Scalar operations
st_mat2 st_mat2_scalar_mult(float c, const st_mat2* a);
float   st_mat2_det(const st_mat2* a);

// Debugging
void    st_mat2_print(const st_mat2* a);



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
st_mat3 st_mat3_mult(const st_mat3* a, const st_mat3* b);
int st_mat3_inverse(st_mat3* dest, const st_mat3* a);

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
st_mat4 st_mat4_transpose(const st_mat4* a);
st_mat4 st_mat4_sum(const st_mat4* a, const st_mat4* b);
st_mat4 st_mat4_sub(const st_mat4* a, const st_mat4* b);
st_mat4 st_mat4_mult(const st_mat4* a, const st_mat4* b);

// Scalar operations
st_mat4 st_mat4_scalar_mult(float c, const st_mat4* a);
float   st_mat4_det(const st_mat4* a);

// Debugging
void    st_mat4_print(const st_mat4* a);


/* Determinant predicates */
float   st_orient2d(st_vec2 a, st_vec2 b, st_vec2 c);
// The following require an st_mat4
/* float   st_orient3d(st_vec3 a, st_vec3 b, st_vec3 c); */
/* float   st_incircle2d(st_vec2 a, st_vec2 b, st_vec2 c, st_vec2 d); */

#endif // STMATH_H
