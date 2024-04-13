#include "../../include/data_structures/FileAllocationTable.hpp"

FileAllocationTable::FileAllocationTable(): m_entries(0) { }

FileAllocationTable::FileAllocationTable(BinaryReader& romReader, uint32_t address, uint32_t size): m_entries(size / (2 * sizeof(uint32_t))) {
	romReader.readBytes(reinterpret_cast<char*>(m_entries.data()), size, address);
}

FileAllocationTable::FileAllocationTable(const FileAllocationTable& fileAllocationTable): m_entries(fileAllocationTable.m_entries) { }

uint16_t FileAllocationTable::getFileAmount() const {
	return static_cast<uint16_t>(m_entries.size());
}

uint32_t FileAllocationTable::getBeginingById(uint16_t fileId) const {
	return m_entries[fileId].begining;
}

uint32_t FileAllocationTable::getEndById(uint16_t fileId) const {
	return m_entries[fileId].end;
}

uint32_t FileAllocationTable::getSizeById(uint16_t fileId) const {
	return m_entries[fileId].getSize();
}

void FileAllocationTable::resizeFile(uint16_t fileId, uint32_t newSize) {
	uint32_t currentRealEnd = ((m_entries[fileId].end - 1) & 0xFFFFFFF0) + 0x10;
	uint32_t newRealEnd = ((m_entries[fileId].begining + newSize - 1) & 0xFFFFFFF0) + 0x10;
	int32_t sizeDifference = newRealEnd - currentRealEnd;

	if (sizeDifference == 0) {
		return;
	}

	for (uint16_t currentFileId = 0; currentFileId < m_entries.size(); currentFileId++) {
		if (m_entries[currentFileId].begining > m_entries[fileId].end) {
			m_entries[currentFileId].begining += sizeDifference;
			m_entries[currentFileId].end += sizeDifference;
		}
	}
}

void FileAllocationTable::writeToFile(BinaryWriter& writer, uint32_t offset) const {
	writer.writeBytes(reinterpret_cast<const char*>(m_entries.data()), m_entries.size() * sizeof(Entry), offset);
}