#ifndef RENDER_H
#define RENDER_H

#include <vector>

#include "src/macros.h"
#include "src/text/text.h"
#include "src/camera/camera.h"

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

    // Display mode
    SDL_DisplayMode currentDisplayMode;
    bool fullscreenMode = false;

    // FPS
    float fps;
    bool showFPS = true;

    // Set variables for game ticker
    Uint32 currentTime;
    Uint32 elapsedTime;

    // Set variables for FPS counter
    Uint32 lastTime = SDL_GetTicks();
    Uint32 frameCount = 0;

    // Text
    TTF_Font* font;

    // ! NOTE: When i first tried to create 2 text objects, the program crashed. 
    // !       Turns out it was because I had used up all the memory on the stack, 
    // !       and therefore have to allocate future objects to the heap instead
    Text *fpsText;

    Text *cameraPositionDebugText;
    Text *cameraRotationDebugText;

    // Camera
    const Camera* camera;

public:
    bool initialized = false;

    Renderer();
    ~Renderer();

    void initialize(const Camera* camera);
    void renderFrame();
    // void renderFrame(const std::vector<Triangle>& triangles);                        // ? For future use
    
    inline void present() {
        // ? Present the backbuffer
        // ? It's currently missing implementation, but it should "swap the buffers"-showing the current frame to the user.
        // ? Since I'm using double buffering, it should also prepare the backbuffer for the next frame.
        // ? I think SDL_RenderPresent does this automatically, but I'm not entirely sure.
        // TODO: Add vsync support
                
        // Present the backbuffer
        SDL_RenderPresent(renderer);
    }                                

    // ? DEPRECATED: No longer used by anything interacting with the public interface of the Renderer class
    // inline void clear(const SDL_Color& color = BLACK) { 
    //     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    //     SDL_RenderClear(renderer); 
    // }

    inline SDL_Window* getWindow() const { return window; }

};


#endif // RENDER_H