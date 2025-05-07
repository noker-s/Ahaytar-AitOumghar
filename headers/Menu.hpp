#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>

enum GameState { MENU, PLAYING, ABOUT, GAME_OVER, WIN };

class Menu {
   public:
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void render(SDL_Renderer* renderer);
    void handleInput(SDL_Event& event, GameState& state, bool& running);

   private:
    SDL_Texture* background;
    SDL_Texture* playButton;
    SDL_Texture* aboutButton;
    SDL_Texture* quitButton;
    int selected;  // 0=Play, 1=About, 2=Quit
    // Button positions
    const SDL_Rect playRect = {270, 200, 100, 50};
    const SDL_Rect aboutRect = {270, 270, 100, 50};
    const SDL_Rect quitRect = {270, 340, 100, 50};
};

#endif // MENU_HPP