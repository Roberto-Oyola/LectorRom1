#pragma once
#include <string>
#include <cstdint>

class RomReader;

class GbaHeader
{
private:
    std::string title;
    std::string gameCode;
    std::string makerCode;
    std::uint8_t softwareVersion;

public:
    bool Read(const RomReader& rom);

    void Print() const;
};