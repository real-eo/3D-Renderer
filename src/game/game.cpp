#include "src/game/game.h"

Game::Game() {
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

    // Load font
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

    // * Map
    // Set map
    // ? setMap("testMapObjectLoader");
    setMap("testMapGround");

    // Load map
    map = getMap();
}


Game::~Game() {
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

    std::cout << "Window and renderer destroyed successfully" << std::endl;
}

void Game::run() {
    windowRunning = true;

    while (windowRunning) {
        // * Handle events
        handleEvents();

        // * Render frame
        renderFrame();

        // * Update the screen
        SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
        SDL_RenderPresent(renderer);
    }
}