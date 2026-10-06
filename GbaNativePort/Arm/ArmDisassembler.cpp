#include "ArmDisassembler.h"
#include "ArmDecoder.h"
#include "../Rom/RomReader.h"

#include <iomanip>
#include <iostream>

void ArmDisassembler::Disassemble(
    const RomReader& rom,
    const ArmDecoder& decoder,
    std::size_t startOffset,
    std::size_t instructionCount
) const
{
    for (std::size_t i = 0; i < instructionCount; i++)
    {
        std::size_t offset =
            startOffset + (i * 4);

        std::uint32_t instruction =
            rom.ReadUInt32(offset);

        std::uint32_t address =
            0x08000000 +
            static_cast<std::uint32_t>(offset);

        std::cout
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << address
            << "  ";

        std::cout
            << std::setw(8)
            << std::setfill('0')
            << instruction
            << "  ";

        Instruction decoded =
            decoder.Decode(
                instruction,
                address
            );

        std::cout
            << decoded.text;

        std::cout << "\n";
    }

    std::cout << std::dec;
}