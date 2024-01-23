#include "Display.h"

void Display::draw(const Memory& memory) {
    /*
    for (int i {0}; i != vram.size(); ++i) {
        const std::uint8_t byte{vram[i]};
        const int col {i * 8 / screenHeight};
        int rowBegin {i * 8 % screenHeight};

        for (int bit {0}; bit != 8; ++bit, ++rowBegin) {
            const int row {screenHeight - rowBegin - 1};

            // transpose the array (rotate 90 degrees counter-clockwise)
            rasterBuffer[row][col] = (byte >> bit) & 0b1 ? 0xFFFFFFFF : 0xFF000000;
        }
    }*/

    SDL_UpdateTexture(texture, nullptr, rasterBuffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Display::off() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
}