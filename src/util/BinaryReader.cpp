#include "../../include/util/BinaryReader.hpp"

const char* BinaryReader::FILE_NOT_FOUND = "Error opening file";
const char* BinaryReader::OFFSET_OUT_OF_BOUNDS = "Offset out of bounds";

BinaryReader::BinaryReader(const char* filename) : m_stream(filename, std::ios::in | std::ios::binary) {
	if (!m_stream.is_open()) {
		throw std::runtime_error(FILE_NOT_FOUND);
	}

	m_stream.seekg(0, std::ios::end);
	m_fileSize = static_cast<size_t>(m_stream.tellg());
	m_stream.seekg(0, std::ios::beg);
}

BinaryReader::~BinaryReader() {
	m_stream.close();
}

BinaryReader& BinaryReader::seekg(std::streampos pos) {
	m_stream.seekg(pos);
	return *this;
}

BinaryReader& BinaryReader::seekg(std::streamoff off, std::ios_base::seekdir way) {
	m_stream.seekg(off, way);
	return *this;
}

size_t BinaryReader::tellg() {
	return static_cast<size_t>(m_stream.tellg());
}

uint8_t BinaryReader::readUInt8() {
	if (static_cast<size_t>(m_stream.tellg()) + sizeof(uint8_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint8_t value;
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint16_t BinaryReader::readUInt16() {
	if (static_cast<size_t>(m_stream.tellg()) + sizeof(uint16_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint16_t value;
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint32_t BinaryReader::readUInt32() {
	if (static_cast<size_t>(m_stream.tellg()) + sizeof(uint32_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint32_t value;
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint64_t BinaryReader::readUInt64() {
	if (static_cast<size_t>(m_stream.tellg()) + sizeof(uint64_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint64_t value;
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint8_t BinaryReader::readUInt8(size_t offset) {
	if(offset + sizeof(uint8_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint8_t value;
	m_stream.seekg(offset);
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint16_t BinaryReader::readUInt16(size_t offset) {
	if (offset + sizeof(uint16_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint16_t value;
	m_stream.seekg(offset);
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint32_t BinaryReader::readUInt32(size_t offset) {
	if (offset + sizeof(uint32_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint32_t value;
	m_stream.seekg(offset);
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

uint64_t BinaryReader::readUInt64(size_t offset) {
	if (offset + sizeof(uint64_t) > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	uint64_t value;
	m_stream.seekg(offset);
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
	return value;
}

void BinaryReader::readBytes(std::vector<uint8_t>& buffer) {
	if (static_cast<size_t>(m_stream.tellg()) + buffer.size() > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	m_stream.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
}

void BinaryReader::readBytes(std::vector<uint8_t>& buffer, size_t offset) {
	if (offset + buffer.size() > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	m_stream.seekg(offset);
	m_stream.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
}

void BinaryReader::readBytes(char* buffer, size_t size) {
	if (static_cast<size_t>(m_stream.tellg()) + size > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	m_stream.read(buffer, size);
}

void BinaryReader::readBytes(char* buffer, size_t size, size_t offset) {
	if (offset + size > m_fileSize) {
		throw std::runtime_error(OFFSET_OUT_OF_BOUNDS);
	}

	m_stream.seekg(offset);
	m_stream.read(buffer, size);
}

void BinaryReader::close() {
	m_stream.close();
}

size_t BinaryReader::size() const {
	return m_fileSize;
}