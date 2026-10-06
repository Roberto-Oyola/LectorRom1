#include <iostream>
#include <iomanip>

#include "Rom/RomReader.h"
#include "Gba/GbaHeader.h"
#include "Arm/ArmDecoder.h"
#include "Arm/ArmDisassembler.h"
#include "Arm/ArmFlowAnalyzer.h"

int main()
{
    RomReader rom;

    const std::string romPath = "C:\\Users\\vm-royola\\Documents\\git\\ROMS_PRUEBAS\\Tetris Worlds (USA).gba";

    if (!rom.LoadRom(romPath))
    {
        return 1;
    }

    GbaHeader header;

    if (!header.Read(rom))
    {
        std::cout << "Error: no se pudo leer el header de la GBA.\n";
        return 1;
    }

    std::cout << "=== GBA ROM READER ===\n\n";

    header.Print();

    std::cout << "\n=== ARM DISASSEMBLY ===\n";

    ArmDecoder decoder;
    /*ArmDisassembler disassembler;

    disassembler.Disassemble(
        rom,
        decoder,
        0xC0,
        10
    );*/

    ArmFlowAnalyzer flowAnalyzer;

    flowAnalyzer.Analyze(
        rom,
        decoder,
        0x08000000,
        100
    );
    return 0;
}