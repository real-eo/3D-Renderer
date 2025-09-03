#pragma once

#ifndef PLAYERLIB_H
#define PLAYERLIB_H

// #include "src/objectEngine/objectEngine.h"           // Included in: "src/camera/camera.h"
#include "src/camera/camera.h"


class Player {
private:
    float speed = 0.05f;
    float sensitivity = 0.002f;
    
    bool freeCam = false;
    Camera camera;

public:
    Vec3 pos;

    Player();
    Player(const Vec3& offset);
    Player(const Vec3& position);
    Player(const Vec3& position, const Vec3& offset);
    ~Player();
};


#endif // PLAYERLIB_H
