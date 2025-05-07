#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <SDL2/SDL.h>

#include <string>

class Object {
   public:
    Object(SDL_Renderer* renderer, const std::string& type, int x, int y);
    ~Object();
    void render(SDL_Renderer* renderer, int scrollOffset);
    SDL_Rect getRect() const;
    SDL_Texture* getTexture() const { return texture; }

    // Prevent copying to avoid issues with raw texture pointer ownership
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    // Explicitly define move operations
    Object(Object&& other) noexcept;             // Move constructor
    Object& operator=(Object&& other) noexcept;  // Move assignment operator

   private:
    SDL_Texture* texture;
    int x, y;
    float scale = 0.7f;  // Scale down to 50% for jumpability
};

#endif  // OBJECTS_HPP