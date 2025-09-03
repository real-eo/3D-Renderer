#pragma once

#ifndef OBJENGINELIB_H
#define OBJENGINELIB_H

#include <vector>
#include <cmath>

#include "logging/logging.h"


// * Define data structures
struct Vec2 {
    float x, y;

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

struct iVec2 {
    int x, y;

    iVec2(int x = 0, int y = 0) : x(x), y(y) {}
};


struct Vec3 {
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator+(const Vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }
};



// Note: This struct isn't intrinsically different from the Point3D-struct, and is more of a semantic distinction
// struct Rotation3D { 
//     float pitch, yaw, roll;

//     Rotation3D(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f) : pitch(pitch), yaw(yaw), roll(roll) {}
// };


// struct RotationMatrix3D {
//     Rotation3D xAxis;
//     Rotation3D yAxis;
//     Rotation3D zAxis;
// };

struct Shape2d {
    std::vector<Vec2> points;
    std::vector<std::vector<int>> edges;
};

struct Shape3d {
    Vec3 position;
    Vec3 rotation;
    std::vector<Vec3> verticeGeometry;
    std::vector<Vec3> vertices;
    std::vector<std::vector<int>> edges;
};

// ! ### [REMOVE IF AIDS] ############################################

// struct Quaternion {
//     float w;        // real part (scalar)
//     float x, y, z;  // imaginary parts (vector)
    
//     // Default constructor - identity quaternion
//     Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

//     // Constructor from components
//     Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
    
//     // Normalize the quaternion
//     void normalize() {
//         float magnitude = sqrtf(w*w + x*x + y*y + z*z);
//         if (magnitude > 0.0f) {
//             float invMag = 1.0f / magnitude;
//             w *= invMag;
//             x *= invMag;
//             y *= invMag;
//             z *= invMag;
//         }
//     }
    
//     // Quaternion multiplication
//     Quaternion operator*(const Quaternion& q) const {
//         return Quaternion(
//             w*q.w - x*q.x - y*q.y - z*q.z,
//             w*q.x + x*q.w + y*q.z - z*q.y,
//             w*q.y - x*q.z + y*q.w + z*q.x,
//             w*q.z + x*q.y - y*q.x + z*q.w
//         );
//     }
    
//     // Conjugate (inverse for unit quaternions)
//     Quaternion conjugate() const {
//         return Quaternion(w, -x, -y, -z);
//     }
// };

// Quaternion eulerToQuaternion(float pitch, float yaw, float roll);

// ! #################################################################

extern "C" {
    Shape3d loadObject(const char path[], const char fileType[]);
}

#endif 
