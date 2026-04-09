#include "math.h"

#include <math.h>

Vec3f32 vec3f32Add(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x + v.x, u.y + v.y, u.z + v.z}};
}

Vec3f32 vec3f32AddScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x + s, u.y + s, u.z + s}};
}

Vec3f32 vec3f32Sub(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x - v.x, u.y - v.y, u.z - v.z}};
}

Vec3f32 vec3f32Mult(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x * v.x, u.y * v.y, u.z * v.z}};
}

Vec3f32 vec3f32MultScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x * s, u.y * s, u.z * s}};
}

Vec3f32 vec3f32DivScalar(Vec3f32 u, f32 s) {
    return (Vec3f32)vec3f32MultScalar(u, (1 / s));
}

f32 vec3f32LengthSquared(Vec3f32 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 vec3f32Length(Vec3f32 v) {
    return sqrt(vec3f32LengthSquared(v));
}

Vec3f32 vec3f32UnitVector(Vec3f32 v) {
    return vec3f32DivScalar(v, vec3f32Length(v));
}

f32 vec3f32Dot(Vec3f32 u, Vec3f32 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec3f32 vec3f32Cross(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){
        {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x}
    };
}
