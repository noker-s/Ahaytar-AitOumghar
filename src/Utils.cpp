#include "Utils.hpp" // Include the header with declarations
    
#include <SDL2/SDL_image.h> // Need this for IMG_Load
#include <string>
#include <iostream> // For error reporting
    
// Load texture from file
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str()); // IMG_Load needs C-style string
    if (!surface) {
        std::cerr << "Failed to load image: " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr; // Return nullptr on failure
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Free the surface immediately
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        // No need to free surface here, already done
    }
    return texture; // Return the texture (or nullptr if creation failed)
}
    
// Render text to texture
SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font,
                        const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color); // TTF needs C-style string
    if (!surface) {
        std::cerr << "Failed to render text: '" << text << "'! TTF Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to create texture from text surface! SDL Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}