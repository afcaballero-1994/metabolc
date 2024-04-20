#ifndef METABOLC_MATHV_H
#define METABOLC_MATHV_H

#include <math.h>

typedef uint8_t u8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef float f32;
typedef double f64;


typedef struct vec2{
    f32 x;
    f32 y;
}Vec2;

f32 lerpf(float a, float b, float t){
    return (1.0f - t) * a + (t * b);
}

Vec2 addVec2(Vec2 a, Vec2 b){
    return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 subVec2(Vec2 a, Vec2 b){
    return (Vec2){a.x - b.x, a.y - b.y};
}

f32 magnitudeVec2(Vec2 a){
    return sqrtf(a.x * a.x) + sqrtf(a.y * a.y);
}

float sqrlLen(Vec2 a){
    return a.x * a.x + a.y * a.y;
}

Vec2 lerpVec2(Vec2 a, Vec2 b, f32 t){
    return (Vec2){lerpf(a.x, a.y, t), lerpf(a.y, b.y, t)};
}

#endif
