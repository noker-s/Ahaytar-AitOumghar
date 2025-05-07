#include "GameOverScreen.hpp"

#include "Utils.hpp"

GameOverScreen::GameOverScreen(SDL_Renderer* renderer, TTF_Font* font)
    : font(font) {
    background =
        loadTexture(renderer, "assets/images/GameWin&Lose/GameOverbg.png");
    overlay = loadTexture(renderer, "assets/images/GameWin&Lose/Game Over.png");
}

GameOverScreen::~GameOverScreen() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(overlay);
}

void GameOverScreen::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect overlayRect = {220, 200, 200, 100};  // Center the overlay
    SDL_RenderCopy(renderer, overlay, nullptr, &overlayRect);

    SDL_Color white = {255, 255, 255, 255};
    const char* text = "Press ENTER to restart, ESC to menu";
    SDL_Texture* textTex = renderText(renderer, font, text, white);
    int w, h;
    SDL_QueryTexture(textTex, nullptr, nullptr, &w, &h);
    SDL_Rect textRect = {320 - w / 2, 340, w, h};
    SDL_RenderCopy(renderer, textTex, nullptr, &textRect);
    SDL_DestroyTexture(textTex);
}

void GameOverScreen::handleInput(SDL_Event& event, GameState& state,
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