#ifndef TEXTLIB_H
#define TEXTLIB_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "src/macros.h"
#include "src/objectEngine/objectEngine.h"

#define FONT_PATH "res/fonts/ebrima.ttf"

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
    inline void freeText();
    inline void createTextTexture();
public:
    Text(iVec2 position, TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor = WHITE);
    Text(const std::string text, const iVec2 position, const SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);
    Text(const std::string& fontPath, int fontSize);
    ~Text();

    void renderText(const std::string& text, int x, int y);
};

#endif // TEXTLIB_H
