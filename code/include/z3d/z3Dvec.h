#ifndef _Z3DVEC_H_
#define _Z3DVEC_H_

#include <stdint.h>

typedef float f32;
typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct {
    f32 x, y;
} z3dVec2f;

typedef struct {
    f32 x, y, z;
} z3dVec3f;

typedef struct {
    s16 x, y, z;
} z3dVec3s;

typedef struct {
    s32 x, y, z;
} z3dVec3i;

typedef struct {
    f32 data[2][3];
} z3d_nn_math_MTX23;

typedef struct {
    f32 data[3][4];
} z3d_nn_math_MTX34;

typedef struct {
    f32 data[4][4];
} z3d_nn_math_MTX44;


#endif