#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"  // Include the header file where Game is defined
#include "Menu.hpp"

class GameOverScreen {
   public:
    GameOverScreen(SDL_Renderer* renderer, TTF_Font* font);
    ~GameOverScreen();
    void render(SDL_Renderer* renderer);
    void handleInput(SDL_Event& event, GameState& state, Game& game);

   private:
    SDL_Texture* background;
    SDL_Texture* overlay;
    TTF_Font* font;
};

#endif  // GAMEOVERSCREEN_HPP