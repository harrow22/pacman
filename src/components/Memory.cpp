#include "Memory.h"
#include <fstream>
#include <iostream>

bool Memory::load(std::uint8_t* array, const std::string& path, const int addr, const int sz)
{
    std::ifstream file {path, std::ios::binary};

    if (!file.is_open()) {
        std::cerr << std::format("error: can't open file '{:s}'.\n", path);
        return false;
    }

    file.read(reinterpret_cast<char*>(array) + addr, sz);

    if (file.bad()) {
        std::cerr << std::format("error [errno={:d}]: failed when reading file '{:s}'.\n", errno, path);
        return false;
    }

    return true;
}

std::uint8_t Memory::read8(const std::uint16_t addr) const
{
    return 0;
}

void Memory::write8(const std::uint16_t addr, const std::uint8_t val)
{

}

std::uint8_t Memory::input(const Memory::Z80 *cpu, const std::uint8_t port) const
{
    return 0;
}

void Memory::output(const Memory::Z80 *cpu, const std::uint8_t port, const std::uint8_t val)
{

}
