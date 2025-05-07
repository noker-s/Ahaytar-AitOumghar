#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL_ttf.h>

#include <memory> //
#include <vector>

#include "Bike.hpp"
#include "Objects.hpp"
#include "Track.hpp"

class Game {
   public:
    Game(SDL_Renderer* renderer, TTF_Font* font);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int state);
    void handleInput(SDL_Event& event);
    bool isGameOver() const;
    bool isWin() const;
    void reset();

   private:
    Track track;
    std::unique_ptr<Bike> bike;  // Use unique_ptr for dynamic management
    std::vector<Object> objects;
    int scrollOffset;
    float timer;
    bool gameOver;
    bool win;
    TTF_Font* font;
    SDL_Renderer* renderer;  // Store renderer for reset
};

#endif  // GAME_HPP