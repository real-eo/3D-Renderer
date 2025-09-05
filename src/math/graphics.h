#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cmath>
#include "src/objectEngine/objectEngine.h"

// Rotation matrix * vector
inline Vec3 rotate(const Vec3& v, float yaw, float pitch) {
    // Yaw (around Y axis)
    float cosy = cosf(yaw),  siny = sinf(yaw);
    float cosp = cosf(pitch), sinp = sinf(pitch);

    Vec3 out;

    out.x = cosy * v.x + siny * v.z;
    out.z = -siny * v.x + cosy * v.z;
    out.y = cosp * v.y - sinp * out.z;
    out.z = sinp * v.y + cosp * out.z;

    return out;
}

// Perspective projection
inline Vec2 project(const Vec3& v, float fov, float aspect, float nearPlane) {
    float f = 1.0f / tanf(fov * 0.5f);          // Note: Multiply by 0.5f instead of dividing by 2.0f for performance
    Vec2 out;

    out.x = (f / aspect) * (v.x / v.z);
    out.y = f * (v.y / v.z);

    return out;
}

#endif // GRAPHICS_H
