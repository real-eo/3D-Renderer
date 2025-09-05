#include "src/render/render.h" 

#include <SDL2/SDL.h>

#include <iostream>


Renderer::Renderer() {
    // * Load font
    font = TTF_OpenFont(FONT_PATH, 16);

    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // * Text
    //// std::cout << "Text contructor call " << std::endl;
    fpsText = new Text({0,  0}, font, renderer);

    cameraPositionDebugText = new Text({0, 30}, font, renderer);
    cameraRotationDebugText = new Text({0, 50}, font, renderer);


}

Renderer::~Renderer() {
    // * Free all text
    delete fpsText;

    delete cameraPositionDebugText;
    delete cameraRotationDebugText;

    // * Close the font
    TTF_CloseFont(font);
    
    // * Destroy the window and renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Renderer::initialize() {
    // * Initialize Libaries
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return; 
    }

    // * Window
    // Create a window
    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        
        return;
    }
    
    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == renderer) {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        
        return;
    }

    std::cout << "Window and renderer created successfully" << std::endl;
}

void Renderer::renderFrame() {
    /* // ? THIS IS THE IMPLEMENTATION USED IN THE PRIMITVE VERSION OF THE RENDERER. THIS CODE IS KEPT FOR REFERENCE, AND DOESN'T CONTAIN ANY BUGS REGARDING THE RENDERING ALGORITHM
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
    */
}

void Renderer::clear(const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    // ? Present the backbuffer
    // ? It's currently missing implementation, but it should "swap the buffers"-showing the current frame to the user.
    // ? Since I'm using double buffering, it should also prepare the backbuffer for the next frame.
    // ? I think SDL_RenderPresent does this automatically, but I'm not entirely sure.
    // TODO: Add vsync support

    // Present the backbuffer
    // SDL_RenderPresent(renderer);
}