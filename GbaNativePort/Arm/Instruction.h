#pragma once

#include <cstdint>
#include <string>

enum class InstructionType
{
    Unknown,
    Branch,
    BranchExchange,
    DataProcessing,
    Move,
    Load,
    Store
};

struct Instruction
{
    std::uint32_t address = 0;
    std::uint32_t opcode = 0;

    InstructionType type = InstructionType::Unknown;

    std::uint32_t destination = 0;

    std::uint32_t rd = 0;
    std::uint32_t rn = 0;

    std::int32_t immediate = 0;

    bool link = false;

    std::uint32_t memoryAddress = 0;
    bool hasMemoryAddress = false;

    std::string text;
};