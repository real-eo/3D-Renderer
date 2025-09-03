#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

// #include "src/objectEngine/objectEngine.h"           // Included in "src/game/camera.h"
#include "src/camera/camera.h"

// =================== Vector and Matrix Helpers ===================

// struct Camera {
//     Vec3 pos {0, 0, -5};

//     float yaw = 0.0f;   // rotation around y-axis
//     float pitch = 0.0f; // rotation around x-axis
// };

// Rotation matrix * vector
Vec3 rotate(const Vec3& v, float yaw, float pitch) {
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
Vec2 project(const Vec3& v, float fov, float aspect, float nearPlane) {
    float f = 1.0f / tanf(fov / 2.0f);
    Vec2 out;
    
    out.x = (f / aspect) * (v.x / v.z);
    out.y = f * (v.y / v.z);

    return out;
}

// =================== Main Program ===================
int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Perspective Projection - Wireframe Cube",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_SetRelativeMouseMode(SDL_TRUE);             // capture mouse
    Camera cam;

    // Cube vertices
    std::vector<Vec3> cube = {
        {-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},    // back face
        {-1,-1, 1},{1,-1, 1},{1,1, 1},{-1,1, 1}     // front face
    };
    // Cube edges
    std::vector<std::pair<int,int>> edges = {
        {0,1},{1,2},{2,3},{3,0}, // back square
        {4,5},{5,6},{6,7},{7,4}, // front square
        {0,4},{1,5},{2,6},{3,7}  // connections
    };

    float fov = M_PI / 3.0f;  // 60 degrees
    float aspect = 800.0f / 600.0f;
    float speed = 0.05f;
    float sensitivity = 0.002f;

    while (running) {
        // =================== Input ===================
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEMOTION) {
                cam.yaw   += e.motion.xrel * sensitivity;
                cam.pitch += e.motion.yrel * sensitivity;
                if (cam.pitch > M_PI/2) cam.pitch = M_PI/2;
                if (cam.pitch < -M_PI/2) cam.pitch = -M_PI/2;
            }
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        Vec3 forward = {sinf(cam.yaw), 0, cosf(cam.yaw)};
        Vec3 right   = {cosf(cam.yaw), 0, -sinf(cam.yaw)};
        if (keystate[SDL_SCANCODE_W]) { cam.pos.x += forward.x * speed; cam.pos.z += forward.z * speed; }
        if (keystate[SDL_SCANCODE_S]) { cam.pos.x -= forward.x * speed; cam.pos.z -= forward.z * speed; }
        if (keystate[SDL_SCANCODE_A]) { cam.pos.x -= right.x   * speed; cam.pos.z -= right.z   * speed; }
        if (keystate[SDL_SCANCODE_D]) { cam.pos.x += right.x   * speed; cam.pos.z += right.z   * speed; }

        // =================== Render ===================
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        for (auto& edge : edges) {
            Vec3 v1 = cube[edge.first];
            Vec3 v2 = cube[edge.second];

            // Transform to camera space
            v1 = v1 - cam.pos;
            v2 = v2 - cam.pos;
            v1 = rotate(v1, -cam.yaw, -cam.pitch);
            v2 = rotate(v2, -cam.yaw, -cam.pitch);

            if (v1.z <= 0 || v2.z <= 0) continue; // behind camera

            // Project
            Vec2 p1 = project(v1, fov, aspect, 0.1f);
            Vec2 p2 = project(v2, fov, aspect, 0.1f);

            // Convert to screen space
            int sx1 = (int)((p1.x + 1) * 0.5f * w);
            int sy1 = (int)((-p1.y + 1) * 0.5f * h);
            int sx2 = (int)((p2.x + 1) * 0.5f * w);
            int sy2 = (int)((-p2.y + 1) * 0.5f * h);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, sx1, sy1, sx2, sy2);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
