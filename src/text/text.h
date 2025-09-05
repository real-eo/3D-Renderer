#ifndef TEXTLIB_H
#define TEXTLIB_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "src/macros.h"
#include "src/objectEngine/objectEngine.h"

#define FONT_PATH "res/fonts/ebrima.ttf"

/// @brief A class for rendering text in the SDL window
class Text {
private:
    // * Variables
    std::string text;
    iVec2 position;

    SDL_Color textColor;
    TTF_Font* font;

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;

    SDL_Renderer* renderer;

    // * Methods
    // ? These methods are inlined here to minimize overhead 
    inline void freeText() {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    inline void createTextTexture() {
        this->textSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->textColor);
        
        /*
        if (this->textSurface == nullptr) {
            std::cerr << "Failed to create Text(\"" << this->text << "\")" << " surface: " << TTF_GetError() << std::endl;
        }
        */

        this->textTexture = SDL_CreateTextureFromSurface(renderer, this->textSurface);
        
        /*
        if (this->textTexture == nullptr) {
            std::cerr << "Failed to create Text(\"" << this->text << "\")" << " texture: " << SDL_GetError() << std::endl;
        }
        */
    }

public:
    Text();
    Text(const iVec2 position, TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor = WHITE);
    Text(const std::string text, const iVec2 position, TTF_Font* font, SDL_Renderer* renderer, const SDL_Color textColor = WHITE);
    // Text(const std::string& fontPath, int fontSize);                                     // ? Unused constructor, considering to either remove it or implement a font loading system 
    ~Text();

    void update(const std::string text);
    void render();
    void debug();
};

#endif // TEXTLIB_H
