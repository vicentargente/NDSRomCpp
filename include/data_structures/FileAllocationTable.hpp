#ifndef FILEALLOCATIONTABLE_HPP
#define FILEALLOCATIONTABLE_HPP

#include <vector>

#include "../util/BinaryReader.hpp"
#include "../util/BinaryWriter.hpp"

class FileAllocationTable {
	struct Entry {
		uint32_t begining;
		uint32_t end;

		uint32_t getSize() const {
			return end - begining;
		}
	};

public:
	FileAllocationTable();
	FileAllocationTable(BinaryReader &romReader, uint32_t address, uint32_t size);
	FileAllocationTable(const FileAllocationTable& fileAllocationTable); // Copy constructor

	uint16_t getFileAmount() const;

	uint32_t getBeginingById(uint16_t fileId) const;
	uint32_t getEndById(uint16_t fileId) const;
	uint32_t getSizeById(uint16_t fileId) const;

	void resizeFile(uint16_t fileId, uint32_t newSize);

	void writeToFile(BinaryWriter &writer, uint32_t offset) const;
private:
	std::vector<Entry> m_entries;
};

#endif