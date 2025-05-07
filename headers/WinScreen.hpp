#ifndef WINSCREEN_HPP
#define WINSCREEN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Menu.hpp"
#include "Game.hpp"  // Include the definition of Game

class WinScreen {
   public:
    WinScreen(SDL_Renderer* renderer, TTF_Font* font);
    ~WinScreen();
    void render(SDL_Renderer* renderer);
    void handleInput(SDL_Event& event, GameState& state, Game& game);

   private:
    SDL_Texture* background;
    TTF_Font* font;
};

#endif  // WINSCREEN_HPP