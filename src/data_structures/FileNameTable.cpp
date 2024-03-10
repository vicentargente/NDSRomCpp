#include "../../include/data_structures/FileNameTable.h"

FileNameTable::FileNameTable() : m_size(0), m_root(std::make_shared<FileNameTable::Directory>(ROOT_DIRECTORY_ID, "root")) {}

FileNameTable::FileNameTable(BinaryReader& romReader, uint32_t offset, uint32_t size) : m_size(size), m_root(std::make_shared<FileNameTable::Directory>(ROOT_DIRECTORY_ID, "root")) {
	size_t originalRomPosition = romReader.tellg();

	romReader.seekg(offset); // Seek to the start of the file name table

	const uint32_t mainTableIndexSize = romReader.readUInt32(); // Size of the main table index (counting this value)
	const uint32_t mainTableAmount = mainTableIndexSize / 8; // Each entry in the index is 8 bytes long

	m_mainTables = std::vector<std::shared_ptr<FileNameTable::Directory>>(mainTableAmount, nullptr);

	m_mainTables[0] = m_root;
	for (uint16_t i = 0; i < mainTableAmount; i++) {
		romReader.seekg(offset + i * 8);

		uint32_t itemOffset = romReader.readUInt32();
		uint16_t firstFileId = romReader.readUInt16();
		uint16_t parentDirectoryId = romReader.readUInt16();

		std::shared_ptr<FileNameTable::Directory> currentDirectory = m_mainTables[i];
		currentDirectory->setItemOffset(itemOffset);
		currentDirectory->setFirstFileId(firstFileId);
		currentDirectory->setParentId(parentDirectoryId);

		// Read the sub files and sub directories
		romReader.seekg(offset + itemOffset); // Global offset to the item pointed by main table
		for (uint8_t nameLength = romReader.readUInt8(); nameLength != 0; nameLength = romReader.readUInt8()) {
			if (nameLength < 0x80) { //File
				char* name = new char[nameLength];
				romReader.readBytes(name, nameLength);
				std::string nameStr(name, nameLength);
				std::shared_ptr<FileNameTable::File> newFile = std::make_shared<FileNameTable::File>(firstFileId++, nameStr);
				currentDirectory->addChild(nameStr, newFile);
				delete[] name;
			}
			else { //Directory
				nameLength -= 0x80;
				char* name = new char[nameLength];
				romReader.readBytes(name, nameLength);
				uint16_t directoryId = romReader.readUInt16();
				std::string nameStr(name, nameLength);
				std::shared_ptr<FileNameTable::Directory> newDirectory = std::make_shared<FileNameTable::Directory>(directoryId, nameStr);
				m_mainTables[directoryId & 0xFFF] = newDirectory;
				currentDirectory->addChild(nameStr, newDirectory);
				delete[] name;
			}
		}
	}

	romReader.seekg(originalRomPosition);
}

uint16_t FileNameTable::getFileIdByPath(const char* path, char dirSeparator) const {
	std::string_view pathView(path);
	std::vector<std::string_view> pathParts;
	for (auto p = pathView.begin();; ++p) {
		auto q = p;
		p = std::find(p, pathView.end(), dirSeparator);
		if(p == q)
			continue;
		pathParts.emplace_back(q, p);
		if (p == pathView.end())
			break;
	}

	std::shared_ptr<FileNameTable::Directory> currentDirectory = m_root;
	for (uint32_t i = pathParts[0] == "root" ? 1 : 0; i < pathParts.size() - 1; i++) {
		currentDirectory = std::dynamic_pointer_cast<FileNameTable::Directory>(currentDirectory->getChild(std::string(pathParts[i])));
	}

	return std::dynamic_pointer_cast<FileNameTable::File>(currentDirectory->getChild(std::string(pathParts.back())))->getId();
}