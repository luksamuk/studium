#include "studium/stmath.h"
#include "studium/core.h"
#include "studium/macros.h"
#include <stddef.h>
#include <string.h>

/* ========================================================================== */
/*                     General helper macros and functions                    */
/* ========================================================================== */

/* Macro with compound literal to zero-fill any vertex or matrix */
#define st_empty(cast) (cast){  0  }

// This macro converts the coordinates of an element a_{i, j} in a matrix
// of the given order to its actual index on memory's linear representation.
// All given indices must be base-0, e.g. a_{1, 2} means i = 0 and j = 1.
#define st_mat_repr_index(i, j, order) (i * order) + j

// This macro converts a memory index for a coordinate on the matrix to
// its real (base-0) representation and store it on out_i and out_j, e.g.
// index 3 on a matrix of order 2 yields i = 0 and j = 1.
#define st_mat_real_indexes(index, order, out_i, out_j) \
    out_i = (size_t)(index / order);			\
    out_j = index - (out_i * order);

/* Generic functions for printing both vertices and matrices */

static void
__st_generic_vec_print(const float* V, size_t sz)
{
    size_t i;
    for(i = 0; i < sz; i++) {
	printf("%04.4f%s",
	       V[i],
	       (i != sz - 1) ? " " : "");
    }
}

static void
__st_generic_mat_print(const float* A, size_t order)
{
    size_t i;
    for(i = 0; i < order * order; i++) {
	printf("%s%04.4f%c",
	       (i % order) == 0 ? "\t" : "",
	       A[i],
	       ((i + 1) % order) == 0 ? '\n' : '\t');
    }
}

/*
 * Generic functions for applying certain operations to vertices.
 * Notice that, due to matrix repr on memory, they can be used on
 * matrices as well.
 */

static void
__st_generic_vec_sum(float* dest, const float* a,
		     const float* b, size_t sz)
{
    size_t i;
    for(i = 0; i < sz; i++)
	dest[i] = a[i] + b[i];
}

static void
__st_generic_vec_sub(float* dest, const float* a,
		     const float* b, size_t sz)
{
    size_t i;
    for(i = 0; i < sz; i++)
	dest[i] = a[i] - b[i];
}

static void
__st_generic_vec_neg(float* dest, const float* a, size_t sz)
{
    size_t i;
    for(i = 0; i < sz; i++)
	dest[i] = -a[i];
}

static void
__st_generic_vec_mult(float* dest, float c, const float* a, size_t sz)
{
    size_t i;
    for(i = 0; i < sz; i++)
	dest[i] = c * a[i];
}

/*
 * Generic functions for matrix operations
 */

// This procedure takes two matrices and calculate c_{i, j}, which compute
// (a_{i, k} * b_{k, j}).
// This procedure assumes a has the number of lines equal to the number of
// columns in b. This number is given in the form of parameter "order".
static float
__st_generic_mat_mult_step(const float* a, const float* b,
			   size_t real_index, size_t order)
{
    size_t i, j;
    st_mat_real_indexes(real_index, order, i, j);
    float sum = 0.0f;
    size_t iter;
    for(iter = 0; iter < order; iter++) {
	sum += a[st_mat_repr_index(i, iter, order)] *
	    b[st_mat_repr_index(iter, j, order)];
    }
    return sum;
}

/* ========================================================================== */
/*                                  st_vec2                                   */
/* ========================================================================== */

st_vec2
st_vec2_zero()
{
    return st_empty(st_vec2);
}

st_vec2
st_vec2_one()
{
    return (st_vec2){1.0f, 1.0f};
}

st_vec2
st_vec2_new(const float values[static 2])
{
    st_vec2 new;
    memcpy(&new, values, sizeof(float) * 2);
    return new;
}

st_vec2
st_vec2_sum(st_vec2 a, st_vec2 b)
{
    st_vec2 sum;
    __st_generic_vec_sum((float*)&sum, (const float*)&a, (const float*)&b, 2);
    return sum;
}

st_vec2
st_vec2_sub(st_vec2 a, st_vec2 b)
{
    st_vec2 sub;
    __st_generic_vec_sub((float*)&sub, (const float*)&a, (const float*)&b, 2);
    return sub;
}

st_vec2
st_vec2_scalar_mult(float c, st_vec2 a)
{
    st_vec2 result;
    __st_generic_vec_mult((float*)&result, c, (const float*)&a, 2);
    return result;
}

st_vec2
st_vec2_neg(st_vec2 a)
{
    st_vec2 neg;
    __st_generic_vec_neg((float*)&neg, (const float*)&a, 2);
    return neg;
}



float
st_vec2_sqdist(st_vec2 a, st_vec2 b)
{
    float deltaX = a.x - b.x,
	deltaY = a.y - b.y;
    return (deltaX * deltaX)
	+ (deltaY * deltaY);
}

float
st_vec2_sqlen(st_vec2 a)
{
    return (a.x * a.x) + (a.y * a.y);
}

float
st_vec2_dot(st_vec2 a, st_vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

void
st_vec2_print(const st_vec2* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to vector");
	return;
    }
    fputs("vec2 { ", stdout);
    __st_generic_vec_print((const float*)a, 2);
    puts(" }");
}

/* ========================================================================== */
/*                                  st_vec3                                   */
/* ========================================================================== */

st_vec3
st_vec3_zero()
{
    return st_empty(st_vec3);
}

st_vec3
st_vec3_one()
{
    return (st_vec3){1.0f, 1.0f, 1.0f};
}

st_vec3
st_vec3_new(const float values[static 3])
{
    st_vec3 new;
    memcpy(&new, values, sizeof(float) * 3);
    return new;
}

st_vec3
st_vec3_sum(st_vec3 a, st_vec3 b)
{
    st_vec3 sum;
    __st_generic_vec_sum((float*)&sum, (const float*)&a, (const float*)&b, 3);
    return sum;
}

st_vec3
st_vec3_sub(st_vec3 a, st_vec3 b)
{
    st_vec3 sub;
    __st_generic_vec_sub((float*)&sub, (const float*)&a, (const float*)&b, 3);
    return sub;
}

st_vec3
st_vec3_scalar_mult(float c, st_vec3 a)
{
    st_vec3 result;
    __st_generic_vec_mult((float*)&result, c, (const float*)&a, 3);
    return result;
}

st_vec3
st_vec3_neg(st_vec3 a)
{
    st_vec3 neg;
    __st_generic_vec_neg((float*)&neg, (const float*)&a, 3);
    return neg;
}

float
st_vec3_sqdist(st_vec3 a, st_vec3 b)
{
    float deltaX = a.x - b.x,
	deltaY = a.y - b.y,
	deltaZ = a.z - b.z;
    return (deltaX * deltaX)
	+ (deltaY * deltaY)
	+ (deltaZ * deltaZ);
}

float
st_vec3_sqlen(st_vec3 a)
{
    return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

float
st_vec3_dot(st_vec3 a, st_vec3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

st_vec3
st_vec3_cross(st_vec3 a, st_vec3 b)
{
    st_vec3 cross;
    cross.x =    (a.y * b.z) - (a.z * b.y);
    cross.y = - ((a.x * b.z) - (a.z * b.x));
    cross.z =    (a.x * b.y) - (a.y * b.x);
    return cross;
}

void
st_vec3_print(const st_vec3* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to vector");
	return;
    }
    fputs("vec3 { ", stdout);
    __st_generic_vec_print((const float*)a, 3);
    puts(" }");
}



/* ========================================================================== */
/*                                  st_vec4                                   */
/* ========================================================================== */

st_vec4
st_vec4_zero()
{
    return st_empty(st_vec4);
}

st_vec4
st_vec4_one()
{
    return (st_vec4){1.0f, 1.0f, 1.0f, 1.0f};
}

st_vec4
st_vec4_new(const float values[static 4])
{
    st_vec4 new;
    memcpy(&new, values, sizeof(float) * 4);
    return new;
}

st_vec4
st_vec4_sum(st_vec4 a, st_vec4 b)
{
    st_vec4 sum;
    __st_generic_vec_sum((float*)&sum, (const float*)&a, (const float*)&b, 4);
    return sum;
}

st_vec4
st_vec4_sub(st_vec4 a, st_vec4 b)
{
    st_vec4 sub;
    __st_generic_vec_sub((float*)&sub, (const float*)&a, (const float*)&b, 4);
    return sub;
}

st_vec4
st_vec4_scalar_mult(float c, st_vec4 a)
{
    st_vec4 result;
    __st_generic_vec_mult((float*)&result, c, (const float*)&a, 4);
    return result;
}

st_vec4
st_vec4_neg(st_vec4 a)
{
    st_vec4 neg;
    __st_generic_vec_neg((float*)&neg, (const float*)&a, 4);
    return neg;
}

float
st_vec4_sqdist(st_vec4 a, st_vec4 b)
{
    float deltaX = a.x - b.x,
	deltaY = a.y - b.y,
	deltaZ = a.z - b.z,
	deltaW = a.w - b.w;
    return (deltaX * deltaX) + (deltaY * deltaY)
	+ (deltaZ * deltaZ) + (deltaW + deltaW);
}

float
st_vec4_sqlen(st_vec4 a)
{
    return (a.x * a.x) + (a.y * a.y)
	+ (a.z * a.z) + (a.w * a.w);
}

float
st_vec4_dot(st_vec4 a, st_vec4 b)
{
    return (a.x * b.x) + (a.y * b.y)
	+ (a.z * b.z) + (a.w * b.w);
}

void
st_vec4_print(const st_vec4* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to vector");
	return;
    }
    fputs("vec4 { ", stdout);
    __st_generic_vec_print((const float*)a, 4);
    puts(" }");
}


/* ========================================================================== */
/*                                  st_mat2                                   */
/* ========================================================================== */

st_mat2
st_mat2_identity()
{
    st_mat2 id = {1.0f, 0.0f,
		  0.0f, 1.0f};
    return id;
}

st_mat2
st_mat2_transpose(const st_mat2* a)
{
    if(!a) {
	st_log_err("matrix operation on NULL reference to matrix");
	return st_empty(st_mat2);
    }
    
    st_mat2 t = {a->a11, a->a21,
		 a->a12, a->a22};
    return t;
}

st_mat2
st_mat2_sum(const st_mat2* a, const st_mat2* b)
{
    if(!a || !b) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return st_empty(st_mat2);
    }
    
    // Take advantage of matrix representation on memory, which is
    // basically a vector of n x m elements
    st_mat2 sum;
    __st_generic_vec_sum((float*)&sum, (const float*)a->A,
			 (const float*)b->A, 4);
    return sum;
}

st_mat2
st_mat2_sub(const st_mat2* a, const st_mat2* b)
{
    if(!a || !b) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return st_empty(st_mat2);
    }
    
    // Take advantage of matrix representation on memory, which is
    // basically a vector of n x m elements
    st_mat2 sub;
    __st_generic_vec_sub((float*)&sub, (const float*)a->A,
			 (const float*)b->A, 4);
    return sub;
}

st_mat2
st_mat2_mult(const st_mat2* a, const st_mat2* b)
{
    st_mat2 mult;
    size_t i;
    for(i = 0; i < 4; i++) {
	mult.A[i] = __st_generic_mat_mult_step(a->A, b->A, i, 2);
    }
    return mult;
}

static inline void
__st_mat2_adjoint(st_mat2* dest, const st_mat2* a)
{
    *dest = (st_mat2) { a->a22, -a->a12,
		       -a->a21,  a->a11 };
}

int
st_mat2_inverse(st_mat2* dest, const st_mat2* a)
{
    if(!dest || !a) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return 1;
    }

    float det = st_mat2_det(a);
    if(det == 0) {
	st_log_err("attempt matrix inversion of matrix with determinant == 0");
	return 1;
    }

    st_mat2 adjoint;
    __st_mat2_adjoint(&adjoint, a);
    *dest = st_mat2_scalar_mult(1.0f / det, &adjoint);
    return 0;
}

st_mat2
st_mat2_scalar_mult(float c, const st_mat2* a)
{
    if(!a) {
	st_log_err("matrix operation on NULL reference to matrix");
	return st_empty(st_mat2);
    }
    
    st_mat2 mult;
    // Take advantage of representation on RAM
    __st_generic_vec_mult((float*)&mult, c, (const float*)a, 4);
    return mult;
}

float
st_mat2_det(const st_mat2* a)
{
    return (a->a11 * a->a22) - (a->a12 * a->a21);
}

void
st_mat2_print(const st_mat2* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to matrix");
	return;
    }
    
    puts("mat2 {");
    __st_generic_mat_print(a->A, 2);
    puts("}");
}


/* ========================================================================== */
/*                                  st_mat3                                   */
/* ========================================================================== */

st_mat3
st_mat3_identity()
{
    st_mat3 id = {1.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0f,
		  0.0f, 0.0f, 1.0f};
    return id;
}

st_mat3
st_mat3_transpose(const st_mat3* a)
{
    if(!a) {
	st_log_err("matrix operation on NULL reference to matrix");
	return st_empty(st_mat3);
    }
    
    st_mat3 t = {a->a11, a->a21, a->a31,
		 a->a12, a->a22, a->a32,
		 a->a13, a->a23, a->a33};
    return t;
}

st_mat3
st_mat3_sum(const st_mat3* a, const st_mat3* b)
{
    if(!a || !b) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return st_empty(st_mat3);
    }
    
    st_mat3 sum;
    __st_generic_vec_sum((float*)&sum, (const float*)a->A,
			 (const float*)b->A, 9);
    return sum;
}

st_mat3
st_mat3_sub(const st_mat3* a, const st_mat3* b)
{
    if(!a || !b) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return st_empty(st_mat3);
    }
    
    st_mat3 sub;
    __st_generic_vec_sub((float*)&sub, (const float*)a->A,
			 (const float*)b->A, 9);
    return sub;
}

st_mat3
st_mat3_mult(const st_mat3* a, const st_mat3* b)
{
    st_mat3 mult;
    size_t i;
    for(i = 0; i < 9; i++) {
	mult.A[i] = __st_generic_mat_mult_step(a->A, b->A, i, 3);
    }
    return mult;
}

static inline void
__st_mat3_adjoint(st_mat3* dest, const st_mat3* a)
{
    *dest = (st_mat3) {
	    (a->a22 * a->a33) - (a->a23 * a->a32),
	    (a->a13 * a->a32) - (a->a12 * a->a33),
	    (a->a12 * a->a23) - (a->a13 * a->a22), // Line 1
	    
	    (a->a23 * a->a31) - (a->a21 * a->a33),
	    (a->a11 * a->a33) - (a->a13 * a->a31),
	    (a->a13 * a->a21) - (a->a11 * a->a23), // Line 2
	
	    (a->a21 * a->a32) - (a->a22 * a->a31),
	    (a->a12 * a->a31) - (a->a11 * a->a32),
	    (a->a11 * a->a22) - (a->a12 * a->a21)  // Line 3
    };
}

int
st_mat3_inverse(st_mat3* dest, const st_mat3* a)
{
    if(!dest || !a) {
	st_log_err("matrix operation on one or two NULL references to matrices");
	return 1;
    }

    float det = st_mat3_det(a);
    if(det == 0) {
	st_log_err("attempt matrix inversion of matrix with determinant == 0");
	return 1;
    }

    st_mat3 adjoint;
    __st_mat3_adjoint(&adjoint, a);
    *dest = st_mat3_scalar_mult(1.0f / det, &adjoint);
    return 0;
}


st_mat3
st_mat3_scalar_mult(float c, const st_mat3* a)
{
    if(!a) {
	st_log_err("arithmetic operation on NULL reference to matrix");
	return st_empty(st_mat3);
    }
    
    st_mat3 mult;
    __st_generic_vec_mult((float*)&mult, c, (const float*)a, 9);
    return mult;
}

float
st_mat3_det(const st_mat3* a)
{
    if(!a) {
	st_log_err("matrix operation on NULL reference to matrix");
	return 0.0f;
    }
    
    // This implementation could be different.
    // Revisit in case of bad performance!
    return a->a11 * ((a->a22 * a->a33) - (a->a23 * a->a32))
	+ a->a12 * ((a->a23 * a->a31) - (a->a21 * a->a33))
	+ a->a13 * ((a->a21 * a->a32) - (a->a22 * a->a31));
}


void
st_mat3_print(const st_mat3* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to matrix");
	return;
    }
    
    puts("mat3 {");
    __st_generic_mat_print(a->A, 3);
    puts("}");
}



/* ========================================================================== */
/*                                  st_mat4                                   */
/* ========================================================================== */

st_mat4
st_mat4_identity()
{
    st_mat4 id = {1.0f, 0.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, 1.0f, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f};
    return id;
}

st_mat4
st_mat4_mult(const st_mat4* a, const st_mat4* b)
{
    st_mat4 mult;
    size_t i;
    for(i = 0; i < 16; i++) {
	mult.A[i] = __st_generic_mat_mult_step(a->A, b->A, i, 4);
    }
    return mult;
}

st_mat4
st_mat4_scalar_mult(float c, const st_mat4* a)
{
     if(!a) {
	st_log_err("arithmetic operation on NULL reference to matrix");
	return st_empty(st_mat4);
    }
     
    st_mat4 mult;
    __st_generic_vec_mult((float*)&mult, c, (const float*)a, 16);
    return mult;
}

void
st_mat4_print(const st_mat4* a)
{
    if(!a) {
	st_log_err("attempt on printing NULL reference to matrix");
	return;
    }
    
    puts("mat4 {");
    __st_generic_mat_print(a->A, 4);
    puts("}");
}

/* ========================================================================== */
/*                           Determinant Predicates                           */
/* ========================================================================== */

float
st_orient2d(st_vec2 a, st_vec2 b, st_vec2 c)
{
    st_mat3 buffer;
    buffer.a11 = a.x; buffer.a12 = a.y; buffer.a13 = 1.0f;
    buffer.a21 = b.x; buffer.a22 = b.y; buffer.a23 = 1.0f;
    buffer.a31 = c.x; buffer.a32 = c.y; buffer.a33 = 1.0f;
    return st_mat3_det(&buffer);
}
