#ifndef TRACK_HPP
#define TRACK_HPP

#include <SDL2/SDL.h>

class Track {
   public:
    Track(SDL_Renderer* renderer);
    ~Track();
    void render(SDL_Renderer* renderer, int scrollOffset);

   private:
    SDL_Texture* background;
    SDL_Texture* startSign;
    SDL_Texture* finishSign;
};

#endif  // TRACK_HPP