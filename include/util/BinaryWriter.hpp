#ifndef BINARYWRITER_HPP
#define BINARYWRITER_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

class BinaryWriter {
public:
	BinaryWriter(const char* fileName);
	~BinaryWriter();
	BinaryWriter& seekp(std::streampos pos);
	BinaryWriter& seekp(std::streamoff off, std::ios_base::seekdir way);
	size_t tellp();

	void writeUInt8(uint8_t value);
	void writeUInt16(uint16_t value);
	void writeUInt32(uint32_t value);
	void writeUInt64(uint64_t value);
	void writeBytes(const std::vector<uint8_t>& buffer);
	void writeBytes(const std::vector<uint8_t>& buffer, size_t offset);
	void writeBytes(const char* buffer, size_t size);
	void writeBytes(const char* buffer, size_t size, size_t offset);
	void close();

private:
	// Atributos
	std::ofstream m_stream;

	// Constantes
	static const char* OPEN_FILE_ERROR;
};
#endif