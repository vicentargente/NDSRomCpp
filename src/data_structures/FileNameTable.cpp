#include "../../include/data_structures/FileNameTable.h"

FileNameTable::FileNameTable() : m_root(std::make_shared<FileNameTable::Directory>(ROOT_DIRECTORY_ID)) {}

FileNameTable::FileNameTable(BinaryReader& romReader, uint32_t offset, uint32_t size): m_root(std::make_shared<FileNameTable::Directory>(ROOT_DIRECTORY_ID)) {
	size_t originalRomPosition = romReader.tellg();

	romReader.seekg(offset); // Seek to the start of the file name table

	const uint32_t mainTableIndexSize = romReader.readUInt32(); // Size of the main table index (counting this value)
	const uint32_t mainTableAmount = mainTableIndexSize / 8; // Each entry in the index is 8 bytes long

	std::vector<MainTable> mainTables(mainTableAmount);

	romReader.seekg(offset);
	for (uint32_t i = 0; i < mainTableAmount; i++) {
		uint32_t itemOffset = romReader.readUInt32();
		uint16_t firstFileId = romReader.readUInt16();
		uint16_t parentDirectoryId = romReader.readUInt16();

		MainTable mainTable{ parentDirectoryId };

		size_t nextMainTableOffset = romReader.tellg(); // Save the offset of the next main table

		// Read the sub files and sub directories
		romReader.seekg(offset + itemOffset); // Global offset to the item pointed by main table
		for (uint8_t nameLength = romReader.readUInt8(); nameLength != 0; nameLength = romReader.readUInt8()) {
			if (nameLength < 0x80) { //File
				char* name = new char[nameLength];
				romReader.readBytes(name, nameLength);
				mainTable.addSubFile({ firstFileId++, std::string(name, nameLength) });
				delete[] name;
			}
			else { //Directory
				nameLength -= 0x80;
				char* name = new char[nameLength];
				romReader.readBytes(name, nameLength);
				mainTable.addSubDirectory({ romReader.readUInt16(), std::string(name, nameLength) });
				delete[] name;
			}
		}

		mainTables[i] = mainTable;
		romReader.seekg(nextMainTableOffset);
	}

	// Create the directory tree
	std::vector<std::shared_ptr<FileNameTable::Directory>> directories(mainTableAmount);
	directories[0] = m_root;
	std::vector<uint32_t> exploredDirectories(mainTableAmount, 0);

	for (uint16_t i = 1; i < mainTableAmount; i++) {
		uint16_t parentIndex = mainTables[i].parentDirectoryId & 0xFFF; // Remove the fixed 0xF000 from the parent directory id to get index
		Entry &currentData = mainTables[parentIndex].subDirectories[exploredDirectories[parentIndex]++];
		directories[i] = std::make_shared<FileNameTable::Directory>(currentData.id);
		directories[parentIndex]->addChild(currentData.name, directories[i]);

		for (Entry& file : mainTables[i].subFiles) {
			directories[i]->addChild(file.name, std::make_shared<FileNameTable::File>(file.id));
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