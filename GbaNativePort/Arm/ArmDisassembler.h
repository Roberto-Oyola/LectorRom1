#pragma once

#include <cstdint>
#include <cstddef>

class RomReader;
class ArmDecoder;

class ArmDisassembler
{
public:
    void Disassemble(
        const RomReader& rom,
        const ArmDecoder& decoder,
        std::size_t startOffset,
        std::size_t instructionCount
    ) const;
};