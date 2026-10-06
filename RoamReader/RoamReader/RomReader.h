#pragma once
#include <vector>
class RomReader
{
	private:
		std::vector<std::uint8_t> data;

	public:
		void loadTestData();
		void PrintBytes();

		std::uint8_t readByte(std::size_t offset);
};

