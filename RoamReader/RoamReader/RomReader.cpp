#include "RomReader.h"
#include <iostream>

void RomReader::loadTestData()
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
    /*for (std::size_t i = 0; i < data.size(); i++)
    {
        std::cout << "Byte " << i
            << ": 0x"
            << std::hex
            << static_cast<int>(data[i])
            << "\n";
    }*/

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
}