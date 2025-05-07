#include "WinScreen.hpp"

#include "Game.hpp"  // Include the Game class header
#include "Utils.hpp"

// Ensure the Game class is properly included

WinScreen::WinScreen(SDL_Renderer* renderer, TTF_Font* font) : font(font) {
    background =
        loadTexture(renderer, "assets/images/GameWin&Lose/GameWinbg.png");
}

WinScreen::~WinScreen() { SDL_DestroyTexture(background); }

void WinScreen::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Color white = {255, 255, 255, 255};
    std::string winText = "YOU WIN !  Press ENTER to restart, ESC to menu";
    SDL_Texture* textTexture = renderText(renderer, font, winText, white);
    int w, h;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
    SDL_Rect textRect = {320 - w / 2, 300, w, h};  // Lowered text position
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}
void WinScreen::handleInput(SDL_Event& event, enum GameState& state,
                            Game& game) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            game.reset();
            state = PLAYING;
        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU;
        }
    }
}