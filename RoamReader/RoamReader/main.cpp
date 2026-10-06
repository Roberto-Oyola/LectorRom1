#include <iostream>

#include "RomReader.h"

int main()
{
    RomReader rom;
    rom.loadTestData();

    std::cout << "=== ROM Reader ===\n\n";

    rom.PrintBytes();

    std::cout << "\nByte 1: "
        << static_cast<int>(rom.readByte(1))
        << "\n";

    return 0;
}