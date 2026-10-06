#pragma once

#include <cstdint>
#include <string>
#include <vector>

class RomReader
{
private:
    std::vector<std::uint8_t> data;

public:
    bool LoadRom(const std::string& filePath);

    std::size_t GetSize() const;

    std::uint8_t ReadByte(std::size_t offset) const;

    std::uint16_t ReadUInt16(std::size_t offset) const;

    std::uint32_t ReadUInt32(std::size_t offset) const;

    void PrintFirstBytes(std::size_t count) const;
};