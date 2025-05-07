#ifndef ABOUTSCREEN_HPP
#define ABOUTSCREEN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "Menu.hpp"  // Include for GameState enum

class AboutScreen {
   public:
    AboutScreen(SDL_Renderer* renderer, TTF_Font* font);
    ~AboutScreen();
    void render(SDL_Renderer* renderer);
    void handleInput(SDL_Event& event,
                     GameState& state);  // Add handleInput method

   private:
    SDL_Texture* background;
    TTF_Font* font;
    std::string instructions;
};

#endif  // ABOUTSCREEN_HPP