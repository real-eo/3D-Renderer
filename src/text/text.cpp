#include "src/text/text.h"


inline void Text::freeText() {
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

inline void Text::createTextTexture() {
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