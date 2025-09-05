#include "src/player/player.h"


Player::Player()                                            : pos({0, 0, 0})    { camera = new Camera(&pos, Vec3(0, 0, 0)); }
Player::Player(const Vec3& position, const Vec3& offset)    : pos(position)     { camera = new Camera(&pos, offset); }

Player::~Player() {
    delete camera;
}

void Player::move(const Uint8* key) {
    // TODO: Look over, and check the implementation
    Vec3 forward = {sinf(camera->yaw), 0, cosf(camera->yaw)};
    Vec3 right   = {cosf(camera->yaw), 0, -sinf(camera->yaw)};

    if (key[SDL_SCANCODE_W]) { pos.x += forward.x * speed; pos.z += forward.z * speed; }
    if (key[SDL_SCANCODE_S]) { pos.x -= forward.x * speed; pos.z -= forward.z * speed; }
    if (key[SDL_SCANCODE_A]) { pos.x -= right.x   * speed; pos.z -= right.z   * speed; }
    if (key[SDL_SCANCODE_D]) { pos.x += right.x   * speed; pos.z += right.z   * speed; }
}

void Player::turn(const int dx, const int dy) {
    // TODO: Look over, and check the implementation
    camera->yaw   += dx * sensitivity;
    camera->pitch += dy * sensitivity;

    // Clamp pitch to [-pi/2, pi/2]
    if (camera->pitch > M_PI / 2)  camera->pitch = M_PI / 2;
    if (camera->pitch < -M_PI / 2) camera->pitch = -M_PI / 2;
}
