#include "Game.hpp"

#include <algorithm>  // For std::max and std::min
#include <iostream>
#include <memory>  // For std::unique_ptr

#include "Menu.hpp"
#include "Utils.hpp"

Game::Game(SDL_Renderer* renderer, TTF_Font* font)
    : track(renderer),
      bike(std::make_unique<Bike>(renderer)),  // Initialize with renderer
      // Use unique_ptr for dynamic management
      scrollOffset(0),
      timer(30.0f),
      gameOver(false),
      win(false),
      font(font),
      renderer(renderer) {  // Store renderer for reset
    objects.push_back(Object(renderer, "fallentree1", 470, 350));
    objects.push_back(Object(renderer, "fallentree2", 710, 350));
    objects.push_back(Object(renderer, "rocks", 900, 350));
    objects.push_back(Object(renderer, "fallentree3", 1100, 350));
    objects.push_back(Object(renderer, "hole", 1340, 350));
    objects.push_back(Object(renderer, "rocks", 1550, 350));
    objects.push_back(Object(renderer, "fallentree1", 1710, 350));
    objects.push_back(Object(renderer, "fallentree2", 1940, 350));
    objects.push_back(Object(renderer, "hole", 2160, 350));
    objects.push_back(Object(renderer, "fallentree3", 2390, 350));
    objects.push_back(Object(renderer, "rocks", 2570, 350));
    objects.push_back(Object(renderer, "fallentree2", 2780, 350));
}

void Game::update(float deltaTime) {
    if (gameOver || win) return;
    bike->update(deltaTime);  // Access via arrow operator
    scrollOffset =
        std::max(0, std::min(static_cast<int>(bike->getX() - 320),
                             3000 - 640));  // Adjusted to prevent overscroll
    // Prevent overscroll
    // Check for collisions with objects
    // Assuming objects is a vector of Object instances
    // and bike is a pointer to the Bike instance
    SDL_Rect bikeRect = bike->getRect();
    for (const auto& obj : objects) {
        SDL_Rect objRect = obj.getRect();
        if (SDL_HasIntersection(&bikeRect, &objRect)) {
            gameOver = true;
            return;
        }
    }
    if (bike->getX() >= 2900) win = true;
    timer -= deltaTime;
    if (timer <= 0) gameOver = true;
}

void Game::render(SDL_Renderer* renderer, int state) {
    track.render(renderer, scrollOffset);
    if (state == PLAYING) {                    // Assuming 1 is PLAYING state
        bike->render(renderer, scrollOffset);  // Access via arrow operator
        for (auto& obj : objects) {
            if (obj.getTexture() == nullptr) {
                std::cout << "Object texture is NULL!" << std::endl;
            }
            obj.render(renderer, scrollOffset);
        }
        std::string timeStr =
            "Time: " + std::to_string(static_cast<int>(timer + 0.5f));
        SDL_Color white = {255, 255, 255, 255};
        SDL_Texture* timeTex = renderText(renderer, font, timeStr, white);
        int w, h;
        SDL_QueryTexture(timeTex, nullptr, nullptr, &w, &h);
        SDL_Rect timeRect = {10, 10, w, h};
        SDL_RenderCopy(renderer, timeTex, nullptr, &timeRect);
        SDL_DestroyTexture(timeTex);
    }
}

void Game::handleInput(SDL_Event& event) {
    bike->handleInput(event);  // Access via arrow operator
}

bool Game::isGameOver() const { return gameOver; }
bool Game::isWin() const { return win; }

void Game::reset() {
    bike = std::make_unique<Bike>(renderer);  // Re-initialize with renderer
    scrollOffset = 0;
    timer = 30.0f;
    gameOver = false;
    win = false;
}