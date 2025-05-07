#include "Menu.hpp"

#include "Utils.hpp"

Menu::Menu(SDL_Renderer* renderer) : selected(0) {
    background =
        loadTexture(renderer, "assets/images/Menu/Background/Menubg.png");
    playButton =
        loadTexture(renderer, "assets/images/Menu/Buttons/PlayButton.png");
    aboutButton =
        loadTexture(renderer, "assets/images/Menu/Buttons/AboutButton.png");
    quitButton =
        loadTexture(renderer, "assets/images/Menu/Buttons/QuitButton.png");
}

Menu::~Menu() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(aboutButton);
    SDL_DestroyTexture(quitButton);
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_RenderCopy(renderer, playButton, nullptr, &playRect);
    SDL_RenderCopy(renderer, aboutButton, nullptr, &aboutRect);
    SDL_RenderCopy(renderer, quitButton, nullptr, &quitRect);

    // Highlight selected option (simple outline)
    SDL_Rect rects[] = {playRect, aboutRect, quitRect};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rects[selected]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
}

void Menu::handleInput(SDL_Event& event, GameState& state, bool& running) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        if (mx >= playRect.x && mx <= playRect.x + playRect.w &&
            my >= playRect.y && my <= playRect.y + playRect.h) {
            state = PLAYING;
        } else if (mx >= aboutRect.x && mx <= aboutRect.x + aboutRect.w &&
                   my >= aboutRect.y && my <= aboutRect.y + aboutRect.h) {
            state = ABOUT;
        } else if (mx >= quitRect.x && mx <= quitRect.x + quitRect.w &&
                   my >= quitRect.y && my <= quitRect.y + quitRect.h) {
            running = false;
        }
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_UP) {
            selected = (selected - 1 + 3) % 3;
        } else if (event.key.keysym.sym == SDLK_DOWN) {
            selected = (selected + 1) % 3;
        } else if (event.key.keysym.sym == SDLK_RETURN) {
            if (selected == 0)
                state = PLAYING;
            else if (selected == 1)
                state = ABOUT;
            else
                running = false;
        }
    }
}