#pragma once
    
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string> // Use std::string for consistency
    
// Forward declarations are good practice in headers
struct SDL_Renderer;
struct SDL_Texture;
struct TTF_Font; // Forward declaration for TTF_Font
    
// Loads an image from a file path into an SDL_Texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    
// Renders text using the specified font and color
SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font,
                        const std::string& text, SDL_Color color);