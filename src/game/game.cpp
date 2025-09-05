#include "src/game/game.h"

Game::Game() {
    // * Rendering
    renderer = new Renderer();
    renderer->initialize();

    // * Map
    // Set map
    // ? setMap("testMapObjectLoader");
    setMap("testMapGround");

    // Load map
    map = getMap();
}


Game::~Game() {
    // Call renderer destructor
    delete renderer;

    std::cout << "Window and renderer destroyed successfully" << std::endl;
}

void Game::handleEvents() {
    /* // ? THIS IS THE IMPLEMENTATION USED IN THE PRIMITVE VERSION OF THE INPUT LOGIC. THIS CODE IS KEPT FOR REFERENCE, AND DOESN'T CONTAIN ANY BUGS REGARDING THE HANDLING OF INPUT EVENTS
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
    */
}

void Game::run() {
    gameRunning = true;

    while (gameRunning) {
        // * Handle events
        handleEvents();

        // * Render frame
        renderer->renderFrame();

        // * Update the screen
        renderer->clear();
        renderer->present();
        // SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
        // SDL_RenderPresent(renderer);
    }
}