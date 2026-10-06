#include "ArmDecoder.h"

#include <sstream>
#include <iomanip>

Instruction ArmDecoder::Decode(
    std::uint32_t instruction,
    std::uint32_t address
) const
{
    Instruction result;

    result.address = address;
    result.opcode = instruction;

    std::uint32_t condition =
        instruction >> 28;

    // ========================================
    // Branch / Branch with Link
    // ========================================

    if ((instruction & 0x0E000000) == 0x0A000000)
    {
        bool link =
            (instruction & 0x01000000) != 0;

        result.link = link;

        std::int32_t immediate =
            static_cast<std::int32_t>(
                instruction & 0x00FFFFFF
                );

        if (immediate & 0x00800000)
        {
            immediate |= 0xFF000000;
        }

        std::int32_t offset =
            immediate << 2;

        std::uint32_t pc =
            address + 8;

        std::int32_t target =
            static_cast<std::int32_t>(pc)
            + offset;

        result.type =
            InstructionType::Branch;

        result.destination =
            static_cast<std::uint32_t>(target);

        result.immediate =
            immediate;

        std::stringstream text;

        text << (link ? "BL" : "B");

        text << "  immediate=0x"
            << std::hex
            << std::setw(6)
            << std::setfill('0')
            << static_cast<std::uint32_t>(immediate);

        text << "  offset=0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << static_cast<std::uint32_t>(offset);

        text << "  target=0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << static_cast<std::uint32_t>(target);

        text << "  condition=0x"
            << std::hex
            << condition;

        result.text = text.str();

        return result;
    }

    // ========================================
    // MSR
    // ========================================

    if ((instruction & 0x0FB0FFF0) == 0x0120F000)
    {
        std::uint32_t rm =
            instruction & 0x0F;

        std::stringstream text;

        text << "MSR CPSR";

        if (instruction & 0x00010000)
        {
            text << "_c";
        }

        if (instruction & 0x00020000)
        {
            text << "_x";
        }

        if (instruction & 0x00040000)
        {
            text << "_s";
        }

        if (instruction & 0x00080000)
        {
            text << "_f";
        }

        text << ", R"
            << rm;

        result.type =
            InstructionType::DataProcessing;

        result.rn = rm;

        result.text =
            text.str();

        return result;
    }

    // ========================================
    // MOV register
    // ========================================

    if ((instruction & 0x0FE000F0) == 0x01A00000)
    {
        std::uint32_t rd =
            (instruction >> 12) & 0x0F;

        std::uint32_t rm =
            instruction & 0x0F;

        result.type =
            InstructionType::DataProcessing;

        result.rd = rd;
        result.rn = rm;

        std::stringstream text;

        text << "MOV R"
            << rd
            << ", R"
            << rm;

        result.text =
            text.str();

        return result;
    }
    // ========================================
    // BX
    // ========================================

    if ((instruction & 0x0FFFFFF0) == 0x012FFF10)
    {
        std::uint32_t rm =
            instruction & 0x0F;

        result.type =
            InstructionType::BranchExchange;

        result.rn = rm;

        std::stringstream text;

        text << "BX R"
            << rm;

        result.text =
            text.str();

        return result;
    }

    // ========================================
    // Data Processing
    // ========================================

    if ((instruction & 0x0C000000) == 0x00000000)
    {
        std::uint32_t opcode =
            (instruction >> 21) & 0x0F;

        bool immediate =
            (instruction & 0x02000000) != 0;

        std::uint32_t rd =
            (instruction >> 12) & 0x0F;

        std::uint32_t rn =
            (instruction >> 16) & 0x0F;

        // MOV immediate
        if (opcode == 0xD && immediate)
        {
            std::uint32_t value =
                instruction & 0xFF;

            result.type =
                InstructionType::DataProcessing;

            result.rd = rd;

            result.immediate =
                static_cast<std::int32_t>(value);

            std::stringstream text;

            text << "MOV R"
                << rd
                << ", #0x"
                << std::hex
                << value;

            result.text = text.str();

            return result;
        }

        // BIC register
        if (opcode == 0xE && !immediate)
        {
            std::uint32_t shiftType =
                (instruction >> 5) & 0x03;

            std::uint32_t shiftAmount =
                (instruction >> 7) & 0x1F;

            std::uint32_t rm =
                instruction & 0x0F;

            result.type =
                InstructionType::DataProcessing;

            result.rd = rd;
            result.rn = rn;

            std::stringstream text;

            text << "BIC R"
                << rd
                << ", R"
                << rn
                << ", R"
                << rm;

            if (shiftAmount != 0)
            {
                const char* shiftName = "LSL";

                if (shiftType == 1)
                {
                    shiftName = "LSR";
                }
                else if (shiftType == 2)
                {
                    shiftName = "ASR";
                }
                else if (shiftType == 3)
                {
                    shiftName = "ROR";
                }

                text << ", "
                    << shiftName
                    << " #"
                    << std::dec
                    << shiftAmount;
            }

            result.text = text.str();

            return result;
        }
    }

    // ========================================
    // Load / Store
    // ========================================

    if ((instruction & 0x0C000000) == 0x04000000)
    {
        bool load =
            (instruction & 0x00100000) != 0;

        bool immediateOffset =
            (instruction & 0x02000000) != 0;

        std::uint32_t rn =
            (instruction >> 16) & 0x0F;

        std::uint32_t rd =
            (instruction >> 12) & 0x0F;

        if (!immediateOffset)
        {
            std::uint32_t offset =
                instruction & 0xFFF;

            if (load && rn == 15)
            {
                std::uint32_t pc =
                    address + 8;

                result.memoryAddress =
                    pc + offset;

                result.hasMemoryAddress =
                    true;
            }

            result.type =
                load
                ? InstructionType::Load
                : InstructionType::Store;

            result.rd = rd;
            result.rn = rn;

            result.immediate =
                static_cast<std::int32_t>(offset);

            std::stringstream text;

            text << (load ? "LDR" : "STR")
                << " R"
                << rd
                << ", [";

            if (rn == 15)
            {
                text << "PC";
            }
            else
            {
                text << "R"
                    << rn;
            }

            if (offset != 0)
            {
                text << ", #0x"
                    << std::hex
                    << offset;
            }

            text << "]";

            result.text = text.str();

            return result;
        }
    }

    // ========================================
    // Unknown
    // ========================================

    result.type =
        InstructionType::Unknown;

    result.text =
        "Unknown instruction";

    return result;
}