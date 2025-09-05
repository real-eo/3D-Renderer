#ifndef CAMERALIB_H
#define CAMERALIB_H

#include "src/objectEngine/objectEngine.h"


class Camera {
private:
    // Rendering
    float fov = M_PI / 3.0f;                // 60 degrees
    float aspect = 800.0f / 600.0f;         // width / height

    // If attached:
    Vec3 pos;                                   // Camera position

    // If NOT attached:
    Vec3 offset;                                // Offset from the entity's position
    const Vec3* entityPos = nullptr;            // Pointer to entity's position (if attached to an entity)
public:
    float yaw;                                  // rotation around y-axis
    float pitch;                                // rotation around x-axis
    const float roll = 0.0f;                    // rotation around z-axis (unused for now)

    Camera();
    Camera(const Vec3& position, float yawAngle, float pitchAngle);
    Camera(const Vec3* entityPosition, const Vec3& offset);
    Camera(const Vec3* entityPosition, const Vec3& offset, float yawAngle, float pitchAngle);
    ~Camera();

    // Delete the copy constructor and assignment operator to prevent copying. This is because the 
    // Camera class contains members, like pointers or references, that make copying unsafe or ambiguous.
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    // ? These two methods return a const value due to me not finding any reason as to why not yet. Feel free to change!
    inline const bool isAttachedToEntity() const { return entityPos != nullptr; }
    inline const Vec3 getPosition() const { return entityPos ? *entityPos + offset : pos; }
    
    // ? These two methods return a const value due to them just being for debugging
    inline const std::string getPositionDebug() const { return std::to_string(static_cast<int>(pos.x)) + ", " + std::to_string(static_cast<int>(pos.y)) + ", " + std::to_string(static_cast<int>(pos.z)); }
    inline const std::string getRotationDebug() const { return std::to_string(yaw) + ", " + std::to_string(pitch) + ", " + std::to_string(roll); }
};

#endif // CAMERALIB_H