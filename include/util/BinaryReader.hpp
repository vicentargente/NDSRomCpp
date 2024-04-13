#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

class BinaryReader {
public:
	BinaryReader(const char* fileName);
	~BinaryReader();
	BinaryReader& seekg(std::streampos pos);
	BinaryReader& seekg(std::streamoff off, std::ios_base::seekdir way);
	size_t tellg();

	uint8_t readUInt8();
	uint16_t readUInt16();
	uint32_t readUInt32();
	uint64_t readUInt64();
	uint8_t readUInt8(size_t offset);
	uint16_t readUInt16(size_t offset);
	uint32_t readUInt32(size_t offset);
	uint64_t readUInt64(size_t offset);

	void readBytes(std::vector<uint8_t>& buffer);
	void readBytes(std::vector<uint8_t>& buffer, size_t offset);
	void readBytes(char* buffer, size_t size);
	void readBytes(char* buffer, size_t size, size_t offset);
	void close();
	size_t size() const;

private:
	// Atributos
	std::ifstream m_stream;
	size_t m_fileSize;

	// Constantes
	static const char* FILE_NOT_FOUND;
	static const char* OFFSET_OUT_OF_BOUNDS;
};

#endif