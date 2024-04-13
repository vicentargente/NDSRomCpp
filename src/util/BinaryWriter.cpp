#include "../../include/util/BinaryWriter.hpp"

const char* BinaryWriter::OPEN_FILE_ERROR = "Error opening file";

BinaryWriter::BinaryWriter(const char* fileName) : m_stream(fileName, std::ios::out | std::ios::binary) {
	if (!m_stream.is_open()) {
		throw std::runtime_error(OPEN_FILE_ERROR);
	}
}

BinaryWriter::~BinaryWriter() {
	m_stream.close();
}

BinaryWriter& BinaryWriter::seekp(std::streampos pos) {
	m_stream.seekp(pos);
	return *this;
}

BinaryWriter& BinaryWriter::seekp(std::streamoff off, std::ios_base::seekdir way) {
	m_stream.seekp(off, way);
	return *this;
}

size_t BinaryWriter::tellp() {
	return static_cast<size_t>(m_stream.tellp());
}

void BinaryWriter::writeUInt8(uint8_t value) {
	m_stream.write(reinterpret_cast<char*>(&value), sizeof(uint8_t));
}

void BinaryWriter::writeUInt16(uint16_t value) {
	m_stream.write(reinterpret_cast<char*>(&value), sizeof(uint16_t));
}

void BinaryWriter::writeUInt32(uint32_t value) {
	m_stream.write(reinterpret_cast<char*>(&value), sizeof(uint32_t));
}

void BinaryWriter::writeUInt64(uint64_t value) {
	m_stream.write(reinterpret_cast<char*>(&value), sizeof(uint64_t));
}

void BinaryWriter::writeBytes(const std::vector<uint8_t>& buffer) {
	m_stream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

void BinaryWriter::writeBytes(const std::vector<uint8_t>& buffer, size_t offset) {
	m_stream.seekp(offset);
	m_stream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

void BinaryWriter::writeBytes(const char* buffer, size_t size) {
	m_stream.write(buffer, size);
}

void BinaryWriter::writeBytes(const char* buffer, size_t size, size_t offset) {
	m_stream.seekp(offset);
	m_stream.write(buffer, size);
}

void BinaryWriter::close() {
	m_stream.close();
}

