#ifndef NDSROM_H
#define NDSROM_H

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "data_structures/Header.hpp"
#include "data_structures/FileNameTable.hpp"
#include "data_structures/FileAllocationTable.hpp"
#include "file/NDSFile.hpp"

class NDSRom {
public:
	NDSRom(const char* filename);

	uint32_t getGameCode() const;

	std::shared_ptr<NDSFile> getFile(uint16_t fileId) const;
	std::shared_ptr<NDSFile> getFile(const char* filename) const;

	void importFile(uint16_t, std::shared_ptr<NDSFile> file);
	void importFile(const char* filename, std::shared_ptr<NDSFile> file);

	void saveToFile(const char* newRomPath);

private:
	const char* m_filePath;
	Header m_header;
	FileNameTable m_fileNameTable;
	FileAllocationTable m_fileAllocationTable;

	std::unordered_map<uint16_t, std::shared_ptr<NDSFile>> m_importedFiles;
};

#endif