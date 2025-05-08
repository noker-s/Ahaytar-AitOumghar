#include "AboutScreen.hpp"

#include <vector>  // For dynamic line storage

#include "Utils.hpp"

AboutScreen::AboutScreen(SDL_Renderer* renderer, TTF_Font* font) : font(font) {
    background = loadTexture(renderer, "assets/images/About/Aboutbg.png");

    instructions =
        "Welcome to Bike Game!\n"
        "How to Play:\n"
        "- Use the RIGHT arrow key to move forward.\n"
        "- Use the UP arrow key to jump.\n\n"
        "Game Objectives:\n"
        "- Navigate your bike through the challenging track.\n"
        "- Avoid obstacles such as rocks, fallen trees,\n and holes."
        "- Reach the finish line before the timer runs out \n(30 "
        "seconds).\n\n"
        "Tips:\n"
        "- Time your jumps carefully to avoid obstacles.\n"
        "- Maintain momentum to clear larger gaps.\n"
        "- Watch out for upcoming obstacles to prepare \nyour moves.\n\n"
        "Credits:\n"
        "- Game Design & Programming: \n"
        "--AHAYTAR MOHAMED\n"
        "--YASSINE AITOUMGHAR\n";
}
AboutScreen::~AboutScreen() { SDL_DestroyTexture(background); }

void AboutScreen::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Color white = {255, 255, 255, 255};

    SDL_Rect textBackgroundRect = {280, 130, 120, 210};

    // Use a vector to dynamically store lines
    std::vector<std::string> lines;
    std::string currentLine;
    for (char c : instructions) {
        if (c == '\n') {
            lines.push_back(
                currentLine);  // Add the completed line to the vector
            currentLine = "";
        } else {
            currentLine += c;
        }
    }
    lines.push_back(currentLine);  // Add the last line

    long unsigned int lineHeight =
        20;  // Reduced line height for tighter spacing
    long unsigned int totalHeight =
        lineHeight * lines.size();  // Use vector size
    long unsigned int startY =
        textBackgroundRect.y + (textBackgroundRect.h - totalHeight) /
                                   2;  // Center text within the black box
    for (long unsigned int i = 0; i < lines.size(); ++i) {
        if (lines[i].empty()) continue;  // Skip rendering empty lines
        SDL_Texture* textTexture = renderText(renderer, font, lines[i],
                                              white);  // Access vector element
        int w, h;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &w,
                         &h);  // Get text dimensions
        SDL_Rect textRect = {
            textBackgroundRect.x + (textBackgroundRect.w - w) / 2,
            static_cast<int>(startY + i * lineHeight), w, h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_DestroyTexture(textTexture);
    }
}

void AboutScreen::handleInput(SDL_Event& event, GameState& state) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU;
        }
        if (event.key.keysym.sym == SDLK_RETURN) {
            state = MENU;
        }
    }
}
