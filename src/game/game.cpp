#include "src/game/game.h"

Game::Game() {
    // * Game
    player = new Player(Vec3(0, 0, -5), Vec3(0, 0, 0));       // Persistent player object

    // * Rendering
    renderer = new Renderer();
    renderer->initialize(player->getCameraPointer());

    // * Map
    // Set map
    // ? setMap("testMapObjectLoader");
    setMap("testMapGround");

    // Load map
    map = getMap();

    // * Game loop
    // Init once
    SDL_SetRelativeMouseMode(SDL_TRUE);                         // raw deltas, no warp
    // SDL_SetWindowGrab(renderer->getWindow(), SDL_TRUE);         // optional: confine cursor. NOTE: Window is managed by the renderer 

    keyboardState = SDL_GetKeyboardState(NULL);
}


Game::~Game() {
    delete renderer;
    delete player;                  // ! Important to delete after renderer, since renderer uses the player's camera

    std::cout << "Window and renderer destroyed successfully" << std::endl;
    std::cout << "Player destroyed successfully" << std::endl;
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
    
    /* // ? THIS IS THE OLD IMPLEMENTATION USED IN THE PREVIOUS VERSION OF THE GAME ENGINE

    // * Movement
    // I have to handle movement events separately because the keyboardState is not necessarily only updated when an SDL_PollEvent is triggered
    camera.move(keyboardState);

    if (SDL_PollEvent(&windowEvent)) {
        if (SDL_QUIT == windowEvent.type) {
            windowRunning = false;
        }

        // * Keyboard
        if (SDL_KEYDOWN == windowEvent.type) {
            switch (windowEvent.key.keysym.sym) {
                case SDLK_F11:
                    if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_ShowCursor(SDL_ENABLE);
                        
                        center = {WIDTH >> 1, HEIGHT >> 1};
                        screenSize = {WIDTH, HEIGHT};

                        fullscreenMode = false;
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                        SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
                        SDL_ShowCursor(SDL_DISABLE);

                        center = {currentDisplayMode.w >> 1, currentDisplayMode.h >> 1};
                        screenSize = {currentDisplayMode.w, currentDisplayMode.h};

                        // Set mouse position to center of screen 
                        SDL_WarpMouseInWindow(window, center.x, center.y);

                        fullscreenMode = true;
                    }

                    // Update the perspective projection constant
                    camera.perspectiveProjectionConstant = screenSize.y / camera.screenHeight_world;

                    break;
                case SDLK_m:
                    std::cout << "Map ID: " << mapID << "\n";

                    switch (mapID % 2) {
                    case 0:
                        setMap("testMapVoid");
                        break;
                    case 1:
                        setMap("testMapGround");

                        mapID = -1; // ! Reset mapID on last map
                        break;
                    }

                    map = getMap();
                    mapID++;

                    break;
                    
                default:
                    // logMessage("Key pressed: " + std::to_string(windowEvent.key.keysym.sym), __LOGGING_TRACE, __MAIN_LOGID);
                    //
                    // cameraMovementSpeed = (cameraMovementSpeedConstant / (static_cast<int>(fps) + 1));
                    // cameraMovementSpeed = cameraMovementSpeedConstant;
                    // cameraMovementSpeed = elapsedTime / 10.0f;
                    //
                    // logMessage("Camera movement speed: " + std::to_string(cameraMovementSpeed), __LOGGING_DEBUG, __MAIN_LOGID);
                    break;
            };
        }

        // * Mouse
        // If window is focused
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
            // Get mouse position
            mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
            mousePosition -= center;
            
            // If mouse is moved
            if (0 != (abs(mousePosition.x) + abs(mousePosition.y)) && fullscreenMode) {
                // Rotate Camera
                camera.rotate({
                    -(mousePosition.y) * 0.001f,
                    -(mousePosition.x) * 0.001f,
                    0.0f
                }, {false, false, false});

                // Set mouse position to center of screen 
                SDL_WarpMouseInWindow(window, center.x, center.y);

                // Update cache- and rotation matrix
            }
        }
    }
    */

    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            gameRunning = false;
        } else if (e.type == SDL_MOUSEMOTION) {
            // Relative mouse deltas -> player/camera
            player->turn(e.motion.xrel, e.motion.yrel);
        }
    }

    player->move(keyboardState);
}

void Game::run() {
    if (!renderer->initialized) {
        std::cerr << "Renderer not initialized!" << std::endl;
        return;
    }

    gameRunning = true;

    while (gameRunning) {
        // * Handle events
        handleEvents();

        // * Render frame
        renderer->renderFrame();

        // * Update the screen
        renderer->present();
        // SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
        // SDL_RenderPresent(renderer);
    }
}