#ifndef PACMAN_MEMORY_H
#define PACMAN_MEMORY_H


#include <cstdint>
#include <array>
#include "z80.h"

class Memory {
public:
    using Z80 = z80<Memory>;

    Memory()
    {
        const std::string dir {"/../../assets/roms/"};
        romLoaded &= load(rom, dir + "pacman.6e", 0, 0x1000);
        romLoaded &= load(rom, dir + "pacman.6f", 0x1000, 0x1000);
        romLoaded &= load(rom, dir + "pacman.6h", 0x2000, 0x1000);
        romLoaded &= load(rom, dir + "pacman.6j", 0x3000, 0x1000);
        romLoaded &= load(colorRom, dir + "82s123.7f", 0, 0x20);
        romLoaded &= load(paletteRom, dir + "82s126.4a", 0, 0x100);
        romLoaded &= load(tileRom, dir + "pacman.5e", 0, 0x1000);
        romLoaded &= load(spriteRom, dir + "pacman.5f", 0, 0x1000);
    }

    [[nodiscard]] std::uint8_t read8(std::uint16_t addr) const;
    void write8(std::uint16_t addr, std::uint8_t val);

    [[nodiscard]] std::uint16_t read16(const std::uint16_t addr) const { return read8(addr + 1) << 8 | read8(addr); }
    void write16(const std::uint16_t addr, const std::uint16_t val) { write8(addr, val & 0xFF); write8(addr + 1, val >> 8); }

    [[nodiscard]] std::uint8_t input(const Z80* cpu, std::uint8_t port) const;
    void output(const Z80* cpu, std::uint8_t port, std::uint8_t val);

    bool romLoaded {false};
    std::uint8_t rom[0x4000] {};
    std::uint8_t vram[0x800] {};
    std::uint8_t ram[0x7F0] {};
    std::uint8_t spriteNum[0x10] {};
    std::uint8_t io[0x100] {};

    std::uint8_t colorRom[0x20] {};
    std::uint8_t paletteRom[0x100] {};
    std::uint8_t tileRom[0x1000] {};
    std::uint8_t spriteRom[0x1000] {};
private:
    static bool load(std::uint8_t*, const std::string& path, int addr, int sz);
};


#endif //PACMAN_MEMORY_H
