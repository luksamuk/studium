#include "studium/stmath.h"
#include "studium/core.h"
#include "studium/macros.h"
#include <stddef.h>

/* ========================================================================== */
/*                                  st_vec2                                   */
/* ========================================================================== */

st_vec2
st_vec2_sum(st_vec2 a, st_vec2 b)
{
    st_vec2 sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    return sum;
}

st_vec2
st_vec2_sub(st_vec2 a, st_vec2 b)
{
    st_vec2 sub;
    sub.x = a.x - b.x;
    sub.y = a.y - b.y;
    return sub;
}

st_vec2
st_vec2_neg(st_vec2 a)
{
    st_vec2 neg;
    neg.x = -a.x;
    neg.y = -a.y;
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


/* ========================================================================== */
/*                                  st_vec3                                   */
/* ========================================================================== */

st_vec3
st_vec3_sum(st_vec3 a, st_vec3 b)
{
    st_vec3 sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    sum.z = a.z + b.z;
    return sum;
}

st_vec3
st_vec3_sub(st_vec3 a, st_vec3 b)
{
    st_vec3 sub;
    sub.x = a.x - b.x;
    sub.y = a.y - b.y;
    sub.z = a.z - b.z;
    return sub;
}


st_vec3
st_vec3_neg(st_vec3 a)
{
    st_vec3 neg;
    neg.x = -a.x;
    neg.y = -a.y;
    neg.z = -a.z;
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



/* ========================================================================== */
/*                     Helper matrix functions and macros                     */
/* ========================================================================== */

#define st_empty(cast) (cast){ 0 }

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
    
    {
	size_t i;
	for(i = 0; i < 9; i++)
	    sum.A[i] = a->A[i] + b->A[i];
    }

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
    
    {
	size_t i;
	for(i = 0; i < 9; i++)
	    sub.A[i] = a->A[i] - b->A[i];
    }

    return sub;
}

/* st_mat3 */
/* st_mat3_mult(const st_mat3* a, const st_mat3* b) */
/* { */
/*     // cij = sum [k=1 to n] (aik * bkj) */
/* } */


st_mat3
st_mat3_scalar_mult(float c, const st_mat3* a)
{
    if(!a) {
	st_log_err("arithmetic operation on NULL reference to matrix");
	return st_empty(st_mat3);
    }
    
    st_mat3 mult;

    {
	size_t i;
	for(i = 0; i < 9; i++)
	    mult.A[i] = c * a->A[i];
    }

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
