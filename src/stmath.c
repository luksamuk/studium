#include "studium/stmath.h"

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
