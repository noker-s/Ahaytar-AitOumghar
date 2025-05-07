#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "AboutScreen.hpp"
#include "Game.hpp"
#include "GameOverScreen.hpp"
#include "Menu.hpp"
#include "WinScreen.hpp"

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Bike Game", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError()
                  << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("assets/fonts/Typographica.ttf", 20);
    if (!font) {
        std::cerr
            << "Failed to load font: assets/fonts/Typographica.ttf! TTF Error: "
            << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize game objects
    GameState state = MENU;
    Menu menu(renderer);
    Game game(renderer, font);
    AboutScreen about(renderer, font);  // Removed font argument
    GameOverScreen gameOver(renderer, font);
    WinScreen winScreen(renderer, font);
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    // Main game loop
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            switch (state) {
                case MENU:
                    menu.handleInput(event, state, running);
                    break;
                case PLAYING:
                    game.handleInput(event);
                    break;
                case ABOUT:
                    about.handleInput(event,
                                      state);  // Use AboutScreen's handler
                    break;
                case GAME_OVER:
                    gameOver.handleInput(event, state, game);
                    break;
                case WIN:
                    winScreen.handleInput(event, state, game);
                    break;
            }
        }

        // Update
        if (state == PLAYING) {
            game.update(deltaTime);
            if (game.isGameOver())
                state = GAME_OVER;
            else if (game.isWin())
                state = WIN;
        }

        // Render
        SDL_RenderClear(renderer);
        switch (state) {
            case MENU:
                menu.render(renderer);
                break;
            case PLAYING:
                game.render(renderer, state);
                break;
            case ABOUT:
                about.render(renderer);
                break;
            case GAME_OVER:
                gameOver.render(renderer);
                break;
            case WIN:
                winScreen.render(renderer);
                break;
        }
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
