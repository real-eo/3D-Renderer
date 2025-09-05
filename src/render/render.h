#ifndef RENDER_H
#define RENDER_H

#include <vector>

#include "src/macros.h"
#include "src/text/text.h"

#define WIDTH 800
#define HEIGHT 600


class Renderer {
private:
    // * Window variables
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Window loop
    SDL_Event windowEvent;
    SDL_Color windowColor = BLACK;
    // bool windowRunning;

    // Display mode
    SDL_DisplayMode currentDisplayMode;
    bool fullscreenMode = false;

    // Text
    TTF_Font* font;

    // ! NOTE: When i first tried to create 2 text objects, the program crashed. 
    // !       Turns out it was because I had used up all the memory on the stack, 
    // !       and therefore have to allocate future objects to the heap instead
    Text *fpsText;

    Text *cameraPositionDebugText;
    Text *cameraRotationDebugText;

public:
    Renderer();
    ~Renderer();

    void initialize();
    void renderFrame();
    // void renderFrame(const std::vector<Triangle>& triangles);                        // ? For future use
    void clear(const SDL_Color& color = BLACK);                                         // ? Clears the screen with the given color (default is black)
    void present();                                                                     // ? See render.cpp for description
};


#endif // RENDER_H