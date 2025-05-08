#include "Objects.hpp"

#include <iostream>

#include "Utils.hpp"

Object::Object(SDL_Renderer* renderer, const std::string& type, int x, int y)
    : x(x), y(y) {
    std::string path = "assets/images/Objects/" + type + ".png";
    texture = loadTexture(renderer, path);
    if (!texture) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        texture = nullptr;  // Explicitly set to nullptr on failure
    }
}

Object::~Object() { SDL_DestroyTexture(texture); }

Object::Object(Object&& other) noexcept
    : texture(other.texture),  // Steal the texture pointer
      x(other.x),
      y(other.y),
      scale(other.scale) {
    other.texture = nullptr;  // Prevent 'other' from deleting the texture
}

Object& Object::operator=(Object&& other) noexcept {
    if (this != &other) {             // Prevent self-assignment
        SDL_DestroyTexture(texture);  // Free existing texture

        // Steal resources from 'other'
        texture = other.texture;
        x = other.x;
        y = other.y;
        scale = other.scale;

        other.texture = nullptr;  // Prevent 'other' from deleting the texture
    }
    return *this;
}

void Object::render(SDL_Renderer* renderer, int scrollOffset) {
    if (!texture) return;  // prevent rendering with a null texture!
    int screenX = x - scrollOffset;
    if (screenX > -50 && screenX < 640) {
        // Only render if within screen bounds
        SDL_Rect destRect = {screenX, y, static_cast<int>(100 * scale),
                             static_cast<int>(100 * scale)};

        // Render the texture normally
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

SDL_Rect Object::getRect() const {
    return {x, y, static_cast<int>(100 * scale), static_cast<int>(100 * scale)};
}
