#include "Bike.hpp"

#include <string>

#include "Utils.hpp"
Bike::Bike(SDL_Renderer* renderer)
    : x(50),
      y(300),  // Adjusted to road center (middle of 480px height)
      vx(0),
      vy(0),
      animationTimer(0),
      currentFrame(0),
      isJumping(false),
      rightPressed(false) {
    for (int i = 1; i <= 9; ++i) {
        std::string path =
            "assets/images/Player/Player" + std::to_string(i) + ".png";
        animationFrames.push_back(loadTexture(renderer, path));
    }
}

Bike::~Bike() {
    for (auto frame : animationFrames) {
        SDL_DestroyTexture(frame);
    }
}

void Bike::update(float deltaTime) {
    vx = rightPressed ? speed : 0;
    x += vx * deltaTime;
    if (isJumping) {
        vy += gravity * deltaTime;
        y += vy * deltaTime;
        if (y >= 300) {
            y = 300;
            vy = 0;
            isJumping = false;
        }
    }
    animationTimer += deltaTime;
    if (animationTimer >= 0.1f) {
        currentFrame = (currentFrame + 1) % 9;
        animationTimer = 0;
    }
}

void Bike::render(SDL_Renderer* renderer, int scrollOffset) {
    int screenX = static_cast<int>(x) - scrollOffset;
    SDL_Rect destRect = {screenX, static_cast<int>(y), 90,
                         90};  // Adjusted size for better visibility
    SDL_RenderCopy(renderer, animationFrames[currentFrame], nullptr, &destRect);
}

void Bike::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RIGHT) rightPressed = true;
        if (event.key.keysym.sym == SDLK_UP && !isJumping) {
            vy = -jumpSpeed * 1.01f;  // Added 1% boost
            isJumping = true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_RIGHT) rightPressed = false;
    }
}

SDL_Rect Bike::getRect() const {
    return {static_cast<int>(x), static_cast<int>(y), 70, 70};  // Adjusted size
}

float Bike::getX() const { return x; }
float Bike::getY() const { return y; }