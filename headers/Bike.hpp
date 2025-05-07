#ifndef BIKE_HPP
#define BIKE_HPP

#include <SDL2/SDL.h>

#include <vector>

class Bike {
   public:
    Bike(SDL_Renderer* renderer);
    ~Bike();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int scrollOffset);
    void handleInput(SDL_Event& event);
    SDL_Rect getRect() const;
    float getX() const;
    float getY() const;
    // Delete the assignment operator to prevent its usage
    Bike& operator=(const Bike&) = delete;

   private:
    float x, y;
    float vx, vy;
    float animationTimer;
    int currentFrame;
    std::vector<SDL_Texture*> animationFrames;
    bool isJumping;
    bool rightPressed;
    const float speed = 200.0f;
    const float jumpSpeed = 340.0f;
    const float gravity = 500.0f;
    const int groundLevel =
        340;  // Adjusted to road center (middle of 480px height)
};

#endif  // BIKE_HPP