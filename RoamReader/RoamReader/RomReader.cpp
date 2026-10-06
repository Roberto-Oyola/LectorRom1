#include "RomReader.h"
#include <iostream>
#include <fstream>
#include <iomanip>

/*void RomReader::loadTestData()
{
    data = {
        0x47,
        0x42,
        0x41,
        0x00,
        0x12,
        0x34,
        0x56,
        0x78
    };
}

void RomReader::PrintBytes()
{
    //for (std::size_t i = 0; i < data.size(); i++)
    //{
    //    std::cout << "Byte " << i
    //        << ": 0x"
    //        << std::hex
    //        << static_cast<int>(data[i])
    //        << "\n";
    //}

    std::uint8_t* pointer = data.data();

    std::cout << "\nDireccion de la ROM: "
        << static_cast<void*>(pointer)
        << "\n";

    std::cout << "Primer byte: "
        << static_cast<int>(*pointer)
        << "\n";
}

std::uint8_t RomReader::readByte(std::size_t offset)
{
    return data[offset];
}*/

bool RomReader::LoadRom(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cout << "No se pudo abrir la ROM.\n";
        return false;
    }

    data = std::vector<std::uint8_t>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    return true;
}

void RomReader::PrintInfo()
{
    std::cout << "=== ROM Information ===\n";

    std::cout << "Size: "
        << data.size()
        << " bytes\n";

    std::cout << "First 10 bytes:\n";

    for (std::size_t i = 0; i < 10 && i < data.size(); i++)
    {
        std::cout << "Byte[" << i << "]: 0x"
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(data[i])
            << "\n";
    }

    std::cout << std::dec;
}