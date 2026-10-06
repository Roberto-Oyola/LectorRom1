#pragma once

#include <cstdint>

class RomReader;
class ArmDecoder;

class ArmFlowAnalyzer
{
public:
    void Analyze(
        const RomReader& rom,
        const ArmDecoder& decoder,
        std::uint32_t startAddress,
        std::uint32_t instructionCount
    ) const;
};