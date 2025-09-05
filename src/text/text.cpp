#include "src/text/text.h"


Text::Text() : text(" "), position(iVec2(0, 0)), textColor(WHITE), font(nullptr), renderer(nullptr) { createTextTexture(); };
Text::Text(const iVec2 position, TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor) 
: position(position), font(font), renderer(renderer), text(" "), textColor(textColor) {
    // !   NOTE: If this string is either empty or greater than 3 capital letters/ 4 lowercase letters, 
    // !         the program will crash. 
    // ? UPDATE: It was because of a stack overflow, and is now fixed (I think)
    
    createTextTexture();
};

Text::Text(const std::string text, const iVec2 position, TTF_Font* font, SDL_Renderer* renderer, const SDL_Color textColor) 
: text(text), position(position), textColor(textColor), font(font), renderer(renderer) {

    createTextTexture();
};


Text::~Text() { 
    freeText(); 
    
    std::cout << "Text(\"" << this->text << "\") destroyed" << std::endl; 
};


void Text::update(const std::string text) {
    this->text = text;

    freeText();
    createTextTexture();
};

void Text::render() {   
    // ? Note: It's been so long since i first wrote this code that I don't remember what the actual fuck the code within the comments does
    //  this->textRect = {position.x, position.y, textSurface->w, textSurface->h};
    SDL_Rect textRect = {position.x, position.y, textSurface->w, textSurface->h};

    /* Compare the renderer's format to the surface format
    SDL_RendererInfo rendererInfo;
    if (SDL_GetRendererInfo(renderer, &rendererInfo) != 0) {
        // Handle error
        std::cerr << "SDL_GetRendererInfo failed: " << SDL_GetError() << std::endl;
    } else {
        // Check if the surface format is supported
        bool formatSupported = false;
        for (Uint32 i = 0; i < rendererInfo.num_texture_formats; i++) {
            if (rendererInfo.texture_formats[i] == textSurface->format->format) {
                formatSupported = true;
                break;
            }
        }

        if (!formatSupported) {
            std::cerr << "Surface format not supported by renderer" << std::endl;
        }
    }
    */

    /*x
    if (SDL_RenderCopy(renderer, textTexture, NULL, &(this->textRect)) != 0) {
        std::cerr << "Failed to render Text(\"" << this->text << "\"): " << SDL_GetError() << std::endl;
    }
    */

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void Text::debug() {
    std::cout << "Text: \"" << text << "\"" << std::endl;
    std::cout << "Position: " << position.x << ", " << position.y << std::endl;
    std::cout << "Color: " << (int)textColor.r << ", " << (int)textColor.g << ", " << (int)textColor.b << ", " << (int)textColor.a << std::endl;
    std::cout << "Is font null: " << (font == nullptr) << std::endl;
    std::cout << "Is renderer null: " << (renderer == nullptr) << std::endl;
    std::cout << "Is textSurface null: " << (textSurface == nullptr) << std::endl;
    std::cout << "Is textTexture null: " << (textTexture == nullptr) << std::endl;
}
