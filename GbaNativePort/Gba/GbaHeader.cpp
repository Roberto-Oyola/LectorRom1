#include "GbaHeader.h"
#include "../Rom/RomReader.h"

#include <iostream>

bool GbaHeader::Read(const RomReader& rom)
{
    try
    {
        title.clear();
        gameCode.clear();
        makerCode.clear();

        for (std::size_t i = 0; i < 12; i++)
        {
            char value = static_cast<char>(rom.ReadByte(0xA0 + i));

            if (value != '\0')
            {
                title += value;
            }
        }

        for (std::size_t i = 0; i < 4; i++)
        {
            char value = static_cast<char>(rom.ReadByte(0xAC + i));

            if (value != '\0')
            {
                gameCode += value;
            }
        }

        for (std::size_t i = 0; i < 2; i++)
        {
            char value = static_cast<char>(rom.ReadByte(0xB0 + i));

            if (value != '\0')
            {
                makerCode += value;
            }
        }

        softwareVersion = rom.ReadByte(0xBC);
    }
    catch (const std::exception&)
    {
        return false;
    }

    return true;
}

void GbaHeader::Print() const
{
    std::cout << "\n=== GBA HEADER ===\n";

    std::cout << "Title: "
        << title
        << "\n";

    std::cout << "Game Code: "
        << gameCode
        << "\n";

    std::cout << "Maker Code: "
        << makerCode
        << "\n";

    std::cout << "Software Version: "
        << static_cast<int>(softwareVersion)
        << "\n";
}