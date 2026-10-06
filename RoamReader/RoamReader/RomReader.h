#pragma once
//#include <vector>
//class RomReader
//{
//	private:
//		std::vector<std::uint8_t> data;
//
//	public:
//		void loadTestData();
//		void PrintBytes();
//
//		std::uint8_t readByte(std::size_t offset);
//};
//


#include <cstdint>
#include <vector>
#include <string>

class RomReader
{
    private:
        std::vector<std::uint8_t> data;

    public:
        bool LoadRom(const std::string& filePath);
        void PrintInfo();
};