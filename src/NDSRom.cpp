#include "../include/NDSRom.hpp"
#include "../include/file/NDSFileByteArray.hpp"

#include "../include/util/BinaryReader.hpp"
#include "../include/util/BinaryWriter.hpp"
#include "../include/util/FileCopier.hpp"

NDSRom::NDSRom(const char* filename) : m_filePath(filename) {
	BinaryReader reader(filename);

	m_header = Header(reader);

	m_fileNameTable = FileNameTable(reader, m_header.getFileNameTableAddress(), m_header.getFileNameTableSize());

	m_fileAllocationTable = FileAllocationTable(reader, m_header.getFileAllocationTableAddress(), m_header.getFileAllocationTableSize());

	reader.close();
}

uint32_t NDSRom::getGameCode() const {
	return m_header.getGameCode();
}

std::shared_ptr<NDSFile> NDSRom::getFile(uint16_t fileId) const {
	auto it = m_importedFiles.find(fileId);
	if (it != m_importedFiles.end()) {
		return it->second;
	}

	uint32_t fileOffset = m_fileAllocationTable.getBeginingById(fileId);
	uint32_t fileSize = m_fileAllocationTable.getSizeById(fileId);

	BinaryReader reader(m_filePath);

	std::shared_ptr<NDSFileByteArray> file = std::make_shared<NDSFileByteArray>(fileSize);
	reader.readBytes(file->data(), fileOffset);

	return file;
}

std::shared_ptr<NDSFile> NDSRom::getFile(const char* ndsFilename) const {
	uint16_t fileId = m_fileNameTable.getFileIdByPath(ndsFilename, '/');
	return NDSRom::getFile(fileId);
}

void NDSRom::importFile(uint16_t fileId, std::shared_ptr<NDSFile> file) {
	m_importedFiles[fileId] = file;
}

void NDSRom::importFile(const char* ndsFilename, std::shared_ptr<NDSFile> file) {
	uint16_t fileId = m_fileNameTable.getFileIdByPath(ndsFilename, '/');
	NDSRom::importFile(fileId, file);
}

void NDSRom::saveToFile(const char* newRomPath) {
	FileAllocationTable modifiedFileAllocationTable(m_fileAllocationTable);

	for (auto it = m_importedFiles.begin(); it != m_importedFiles.end(); it++) {
		uint16_t fileId = it->first;
		std::shared_ptr<NDSFile> file = it->second;

		modifiedFileAllocationTable.resizeFile(fileId, file->size());
	}

	BinaryReader reader(m_filePath);
	BinaryWriter writer(newRomPath);

	FileCopier fileCopier; // Allocates copy buffer

	fileCopier.copy(reader, 0x180, writer, 0x180, 0x4000 - 0x180); // Copy full header (skipping the data)

	// Copy the full code
	fileCopier.copy(reader, m_header.getArm9RomAddress(), writer, m_header.getArm9RomAddress(), m_header.getArm9Size());
	fileCopier.copy(reader, m_header.getArm9OverlayAddress(), writer, m_header.getArm9OverlayAddress(), m_header.getArm9OverlaySize());
	fileCopier.copy(reader, m_header.getArm7RomAddress(), writer, m_header.getArm7RomAddress(), m_header.getArm7Size());
	fileCopier.copy(reader, m_header.getArm7OverlayAddress(), writer, m_header.getArm7OverlayAddress(), m_header.getArm7OverlaySize());

	// Copy the full banner
	uint32_t bannerSize = 0x20 + 0x20 + 0x200 + 6 * 0x100;
	fileCopier.copy(reader, m_header.getIconBannerAddress(), writer, m_header.getIconBannerAddress(), bannerSize);

	// Copy the full FNT
	m_fileNameTable.writeToFile(writer, m_header.getFileNameTableAddress());

	// Copy the full FAT
	modifiedFileAllocationTable.writeToFile(writer, m_header.getFileAllocationTableAddress());

	// Copy the files
	for (uint16_t fileId = 0; fileId < m_fileAllocationTable.getFileAmount(); fileId++) {
		auto it = m_importedFiles.find(fileId);

		if (it != m_importedFiles.end()) {
			std::shared_ptr<NDSFile> file = it->second;
			file->writeToFile(writer, modifiedFileAllocationTable.getBeginingById(fileId));
		}
		else {
			fileCopier.copy(reader, m_fileAllocationTable.getBeginingById(fileId), writer, modifiedFileAllocationTable.getBeginingById(fileId), m_fileAllocationTable.getSizeById(fileId));
		}
	}

	m_header.setNtrRegionRomSize(static_cast<uint32_t>(writer.tellp()));

	// Copy the header data
	m_header.writeToFile(writer);

	reader.close();
	writer.close();
}