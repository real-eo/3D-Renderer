#ifndef GAMELIB_H
#define GAMELIB_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// #include "src/objectEngine/objectEngine.h"           // Included in: "src/camera/camera.h"
// #include "src/camera/camera.h"                       // Included in: "src/player/player.h"
#include "src/player/player.h"
#include "src/text/text.h"
#include "src/maps/maps.h"


// * Constants
// Window
#define WIDTH 800
#define HEIGHT 600

// Colors
#define WHITE SDL_Color{255, 255, 255, 255}
#define BLACK SDL_Color{0, 0, 0, 255}
#define GRAY SDL_Color{128, 128, 128, 255}

#define RED SDL_Color{255, 0, 0, 255}
#define GREEN SDL_Color{0, 255, 0, 255}
#define BLUE SDL_Color{0, 0, 255, 255}

#define YELLOW SDL_Color{255, 255, 0, 255}
#define CYAN SDL_Color{0, 255, 255, 255}
#define MAGENTA SDL_Color{255, 0, 255, 255}



class Game {
private:
    // * Window variables
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Font
    // TTF_Font* font;

    // * Variables for the window loop
    // Window loop
    SDL_Event windowEvent;
    SDL_Color windowColor = BLACK;
    bool windowRunning;
    
    // Display mode
    SDL_DisplayMode currentDisplayMode;
    bool fullscreenMode = false;
    
    // FPS
    float fps;
    bool showFPS = true;

    // Set the center of the coordinate system
    Vec2 center = {WIDTH / 2, HEIGHT / 2};
    Vec2 screenSize = {WIDTH, HEIGHT};

    // Text
    // ! NOTE: When i first tried to create 2 text objects, the program crashed. 
    // !       Turns out it was because I had used up all the memory on the stack, 
    // !       and therefore have to allocate future objects to the heap instead
    Text *fpsText;

    Text *cameraPositionDebugText;
    Text *cameraRotationDebugText;

    // * Map
    Map map;
    // "testMapVoid": 0, "testMapGround": 1, "testMapObjectLoader": N/A
    int mapID = 0;

    // * Input
    // Get keyboard
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    // Get mouse
    iVec2 mousePosition;
    Uint32 mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    // * Game loop
    // Set variables for game ticker
    Uint32 currentTime;
    Uint32 elapsedTime;

    // Set variables for FPS counter
    Uint32 lastTime = SDL_GetTicks();
    Uint32 frameCount = 0;

    // * Methods
public:
    Game();
    ~Game();

    void run();
};

#endif // GAMELIB_H