#pragma once

#define vec2Prototype(type)                                                    \
    typedef union U_Vec2##type {                                               \
        type elements[2];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s, u;                                               \
            };                                                                 \
            union {                                                            \
                type y, g, t, v;                                               \
            };                                                                 \
        };                                                                     \
    } Vec2##type;

vec2Prototype(f32);
vec2Prototype(f64);

#define vec3Prototype(type)                                                    \
    typedef union U_Vec3##type {                                               \
        type elements[3];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s, u;                                               \
            };                                                                 \
            union {                                                            \
                type y, g, t, v;                                               \
            };                                                                 \
            union {                                                            \
                type z, b, p, w;                                               \
            };                                                                 \
        };                                                                     \
    } Vec3##type;

vec3Prototype(f32);
vec3Prototype(f64);

Vec3f32 vec3f32Add(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32AddScalar(Vec3f32 u, f32 s);
Vec3f32 vec3f32Sub(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32Mult(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32MultScalar(Vec3f32 u, f32 s);
Vec3f32 vec3f32DivScalar(Vec3f32 u, f32 s);
f32 vec3f32LengthSquared(Vec3f32 v);
f32 vec3f32Length(Vec3f32 v);
Vec3f32 vec3f32UnitVector(Vec3f32 v);
f32 vec3f32Dot(Vec3f32 u, Vec3f32 v);
Vec3f32 vec3f32Cross(Vec3f32 u, Vec3f32 v);

#define vec4Prototype(type)                                                    \
    typedef union U_Vec4##type {                                               \
        type elements[4];                                                      \
        struct {                                                               \
            union {                                                            \
                type x, r, s;                                                  \
            };                                                                 \
            union {                                                            \
                type y, g, t;                                                  \
            };                                                                 \
            union {                                                            \
                type z, b, p;                                                  \
            };                                                                 \
            union {                                                            \
                type w, a, q;                                                  \
            };                                                                 \
        };                                                                     \
    } Vec4##type;

vec4Prototype(f32);
vec4Prototype(f64);
