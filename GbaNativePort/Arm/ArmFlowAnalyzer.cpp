#include "ArmFlowAnalyzer.h"

#include "ArmDecoder.h"
#include "Instruction.h"
#include "../Rom/RomReader.h"

#include <iomanip>
#include <iostream>
#include <unordered_set>

void ArmFlowAnalyzer::Analyze(
    const RomReader& rom,
    const ArmDecoder& decoder,
    std::uint32_t startAddress,
    std::uint32_t instructionCount
) const
{
    std::uint32_t currentAddress =
        startAddress;

    std::unordered_set<std::uint32_t> visited;

    for (std::uint32_t i = 0; i < instructionCount; i++)
    {
        // ========================================
        // Verificar si ya visitamos esta dirección
        // ========================================

        if (visited.find(currentAddress) != visited.end())
        {
            std::cout
                << "Flujo vuelve a una direccion ya analizada: 0x"
                << std::hex
                << currentAddress
                << "\n";

            break;
        }

        visited.insert(currentAddress);

        // ========================================
        // Verificar dirección GBA
        // ========================================

        if (currentAddress < 0x08000000)
        {
            std::cout
                << "Direccion fuera de ROM GBA.\n";

            break;
        }

        std::uint32_t romOffset =
            currentAddress - 0x08000000;

        if (romOffset + 4 > rom.GetSize())
        {
            std::cout
                << "Direccion fuera de los limites de la ROM.\n";

            break;
        }

        // ========================================
        // Leer instrucción
        // ========================================

        std::uint32_t opcode =
            rom.ReadUInt32(romOffset);

        Instruction instruction =
            decoder.Decode(
                opcode,
                currentAddress
            );

        // ========================================
        // Mostrar
        // ========================================

        std::cout
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << currentAddress
            << "  ";

        std::cout
            << std::setw(8)
            << std::setfill('0')
            << opcode
            << "  ";

        std::cout
            << instruction.text
            << "\n";

        // ========================================
        // Branch
        // ========================================

        if (instruction.type == InstructionType::Branch)
        {
            if (instruction.link)
            {
                // BL:
                // es una llamada, no un salto permanente.
                currentAddress += 4;
            }
            else
            {
                // B:
                // cambiar directamente al destino.
                currentAddress =
                    instruction.destination;
            }

            continue;
        }

        if (instruction.type == InstructionType::BranchExchange)
        {
            std::cout
                << "BX requiere conocer el valor de R"
                << instruction.rn
                << ". Flujo indirecto.\n";

            break;
        }

        // ========================================
        // Siguiente instrucción
        // ========================================

        currentAddress += 4;
    }

    std::cout << std::dec;
}