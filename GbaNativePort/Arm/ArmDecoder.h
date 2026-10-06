#pragma once

#include "Instruction.h"
#include <cstdint>

class ArmDecoder
{
public:
    Instruction Decode(
        std::uint32_t instruction,
        std::uint32_t address
    ) const;
};