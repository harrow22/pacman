#ifndef PACMAN_DISPLAY_H
#define PACMAN_DISPLAY_H


#include <cstdint>
#include "SDL.h"
#include "Memory.h"

class Display {
public:
    Display()
    {
        window = SDL_CreateWindow(
                "Space Invaders",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                screenWidth * scaleFactor,
                screenHeight * scaleFactor,
                SDL_WINDOW_SHOWN);
        if (!window) {
            SDL_Log("SDL_CreateWindow() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!renderer){
            SDL_Log("SDL_CreateRenderer() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        texture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_ABGR8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    screenWidth, screenHeight);
        if (!texture){
            SDL_Log("SDL_CreateTexture() failed. SDL_Error: %s\n", SDL_GetError());
            return;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

        // initialize screen
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        active = true;
    }
    void draw(const Memory& memory);
    void off();

    bool active {false};
private:
    // display constants
    static constexpr int screenWidth {224};
    static constexpr int screenHeight {256};
    static constexpr int scaleFactor {3};
    static constexpr int pitch {screenWidth * sizeof(std::uint32_t)};

    std::uint32_t rasterBuffer[screenHeight][screenWidth] {};
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    SDL_Texture* texture {nullptr};
};


#endif //PACMAN_DISPLAY_H
