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

    Camera();
    Camera(const Vec3& position, float yawAngle, float pitchAngle);
    Camera(const Vec3* entityPosition, const Vec3& offset);
    Camera(const Vec3* entityPosition, const Vec3& offset, float yawAngle, float pitchAngle);
    ~Camera();

    bool isAttachedToEntity() const { return entityPos != nullptr; }
    Vec3 getPosition() const { return entityPos ? *entityPos + offset : pos; }
};

#endif // CAMERALIB_H