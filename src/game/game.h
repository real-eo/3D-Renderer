#ifndef GAMELIB_H
#define GAMELIB_H

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>

// #include "src/objectEngine/objectEngine.h"           // Included in: "src/camera/camera.h"
// #include "src/camera/camera.h"                       // Included in: "src/player/player.h"
#include "src/player/player.h"
// #include "src/text/text.h"                           // Included in: "src/render/render.h"
#include "src/maps/maps.h"
#include "src/render/render.h"


class Game {
private:
    // * Window variables
    // SDL_Window *window;
    // SDL_Renderer *renderer;

    // Font
    // TTF_Font* font;

    // * Renderer
    Renderer *renderer;

    // * Variables for the window loop
    // // Window loop
    // SDL_Event windowEvent;
    // SDL_Color windowColor = BLACK;
    bool gameRunning;
    
    // Set the center of the coordinate system
    // | Both vars are per now unused
    // Vec2 center = {WIDTH / 2, HEIGHT / 2};
    // Vec2 screenSize = {WIDTH, HEIGHT};

    // * Game
    Player* player;

    // * Map
    Map map;
    int mapID = 0;                                                                      // ? "testMapVoid": 0, "testMapGround": 1, "testMapObjectLoader": N/A

    // * Input
    // Get keyboard
    const Uint8 *keyboardState;

    // Get mouse
    // ? OUTDATED:
    // iVec2 mousePosition;
    // Uint32 mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);


    // * Methods
    void handleEvents();
public:
    Game();
    ~Game();

    void run();
};

#endif // GAMELIB_H