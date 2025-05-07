#include "Track.hpp"

#include "Utils.hpp"

Track::Track(SDL_Renderer* renderer) {
    background = loadTexture(renderer, "assets/images/Track/background.png");
    startSign =
        loadTexture(renderer, "assets/images/Start&Finish/StartPoint.png");
    finishSign =
        loadTexture(renderer, "assets/images/Start&Finish/FinishPoint.png");
}

Track::~Track() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(startSign);
    SDL_DestroyTexture(finishSign);
}

void Track::render(SDL_Renderer* renderer, int scrollOffset) {
    SDL_Rect srcRect = {scrollOffset, 0, 640, 480};
    SDL_Rect destRect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, background, &srcRect, &destRect);
    int startX = 50 - scrollOffset;
    int startY = 250;
    if (startX > -100 && startX < 640) {
        SDL_Rect startRect = {startX, startY, 310, 280};  // Increased size
        SDL_RenderCopy(renderer, startSign, nullptr, &startRect);
    }
    int finishX = 2900 - scrollOffset;
    int finishY = 250;
    // Adjusted finishY to match startY
    if (finishX > -100 && finishX < 640) {
        SDL_Rect finishRect = {finishX, finishY, 310, 280};  // Increased size
        SDL_RenderCopy(renderer, finishSign, nullptr, &finishRect);
    }
}