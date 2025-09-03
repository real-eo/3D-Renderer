#include "src/camera/camera.h"


Camera::Camera() : pos{0, 0, 0}, yaw{0}, pitch{0} {}
Camera::Camera(const Vec3& position, float yawAngle, float pitchAngle) : pos(position), yaw(yawAngle), pitch(pitchAngle) {}

Camera::Camera(const Vec3* entityPosition, const Vec3& offset) 
    : offset(offset), entityPos(entityPosition), yaw(0), pitch(0) {
}

Camera::Camera(const Vec3* entityPosition, const Vec3& offset, float yawAngle, float pitchAngle) 
    : offset(offset), entityPos(entityPosition), yaw(yawAngle), pitch(pitchAngle) {
}

Camera::~Camera() {}