#ifndef PLAYERLIB_H
#define PLAYERLIB_H

#include <SDL2/SDL.h>

// #include "src/objectEngine/objectEngine.h"           // Included in: "src/camera/camera.h"
#include "src/camera/camera.h"


class Player {
private:
    float speed = 0.05f;
    float sensitivity = 0.002f;
    
    bool freeCam = false;
    Camera* camera;

public:
    Vec3 pos;

    Player();
    Player(const Vec3& position = Vec3(0, 0, 0), const Vec3& offset = Vec3(0, 0, 0));
    ~Player();

    inline const Camera* getCameraPointer() const { return camera; }

    void move(const Uint8* key);
    void turn(const int dx, const int dy);
};


#endif // PLAYERLIB_H
