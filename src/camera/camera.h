#ifndef CAMERALIB_H
#define CAMERALIB_H

#include "src/objectEngine/objectEngine.h"


class Camera {
private:

public:
    Vec3 pos;
    float yaw = 0.0f;   // rotation around y-axis
    float pitch = 0.0f; // rotation around x-axis

    Camera() : pos{0, 0, -5}, yaw{0}, pitch{0} {}
    Camera(const Vec3& position, float yawAngle, float pitchAngle) : pos(position), yaw(yawAngle), pitch(pitchAngle) {}

};

#endif // CAMERALIB_H