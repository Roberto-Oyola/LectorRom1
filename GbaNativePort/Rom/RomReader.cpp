#include "RomReader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>

bool RomReader::LoadRom(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cerr << "Error: no se pudo abrir la ROM.\n";
        return false;
    }

    data = std::vector<std::uint8_t>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    if (data.empty())
    {
        std::cerr << "Error: la ROM esta vacia.\n";
        return false;
    }

    return true;
}

std::size_t RomReader::GetSize() const
{
    return data.size();
}

void RomReader::PrintFirstBytes(std::size_t count) const
{
    const std::size_t bytesToPrint =
        (count < data.size()) ? count : data.size();

    for (std::size_t i = 0; i < bytesToPrint; i++)
    {
        std::cout
            << "Byte[" << std::dec << i << "]: 0x"
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(data[i])
            << "\n";
    }

    std::cout << std::dec;
}

std::uint8_t RomReader::ReadByte(std::size_t offset) const
{
    if (offset >= data.size())
    {
        throw std::out_of_range("Offset fuera de los limites de la ROM.");
    }

    return data[offset];
}

std::uint16_t RomReader::ReadUInt16(std::size_t offset) const
{
    if (offset + sizeof(std::uint16_t) > data.size())
    {
        throw std::out_of_range("Offset fuera de los limites de la ROM.");
    }

    std::uint16_t value =
        static_cast<std::uint16_t>(data[offset]) |
        (static_cast<std::uint16_t>(data[offset + 1]) << 8);

    return value;
}

std::uint32_t RomReader::ReadUInt32(std::size_t offset) const
{
    if (offset + sizeof(std::uint32_t) > data.size())
    {
        throw std::out_of_range("Offset fuera de los limites de la ROM.");
    }

    std::uint32_t value =
        static_cast<std::uint32_t>(data[offset]) |
        (static_cast<std::uint32_t>(data[offset + 1]) << 8) |
        (static_cast<std::uint32_t>(data[offset + 2]) << 16) |
        (static_cast<std::uint32_t>(data[offset + 3]) << 24);

    return value;
}