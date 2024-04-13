#include "../../include/file/NDSFileByteArray.hpp"
#include "../../include/util/BinaryReader.hpp"

NDSFileByteArray::NDSFileByteArray(uint32_t fileSize) : m_data(fileSize) {}

uint8_t NDSFileByteArray::readUInt8(size_t offset) const {
	return m_data[offset];
}

uint16_t NDSFileByteArray::readUInt16(size_t offset) const {
	return *reinterpret_cast<const uint16_t*>(&m_data[offset]);
}

uint32_t NDSFileByteArray::readUInt32(size_t offset) const {
	return *reinterpret_cast<const uint32_t*>(&m_data[offset]);
}

uint64_t NDSFileByteArray::readUInt64(size_t offset) const {
	return *reinterpret_cast<const uint64_t*>(&m_data[offset]);
}

void NDSFileByteArray::readBytes(std::vector<uint8_t>& buffer, size_t offset) const {
	buffer = std::vector<uint8_t>(m_data.begin() + offset, m_data.end());
}

void NDSFileByteArray::writeUInt8(size_t offset, uint8_t value) {
	if (offset >= m_data.size()) {
		m_data.resize(offset + sizeof(uint8_t));
	}

	m_data[offset] = value;
}

void NDSFileByteArray::writeUInt16(size_t offset, uint16_t value) {
	if (offset + sizeof(uint16_t) > m_data.size()) {
		m_data.resize(offset + sizeof(uint16_t));
	}

	*reinterpret_cast<uint16_t*>(&m_data[offset]) = value;
}

void NDSFileByteArray::writeUInt32(size_t offset, uint32_t value) {
	if (offset + sizeof(uint32_t) > m_data.size()) {
		m_data.resize(offset + sizeof(uint32_t));
	}

	*reinterpret_cast<uint32_t*>(&m_data[offset]) = value;
}

void NDSFileByteArray::writeUInt64(size_t offset, uint64_t value) {
	if (offset + sizeof(uint64_t) > m_data.size()) {
		m_data.resize(offset + sizeof(uint64_t));
	}

	*reinterpret_cast<uint64_t*>(&m_data[offset]) = value;
}

void NDSFileByteArray::writeBytes(const std::vector<uint8_t>& buffer, size_t offset) {
	if (offset + buffer.size() > m_data.size()) {
		m_data.resize(offset + buffer.size());
	}

	std::copy(buffer.begin(), buffer.end(), m_data.begin() + offset);
}

void NDSFileByteArray::setContent(const std::vector<uint8_t>& content) {
	m_data = content;
}

void NDSFileByteArray::setContent(const char* filePath) {
	BinaryReader reader(filePath);
	m_data.resize(reader.size());
	reader.readBytes(m_data, 0);
}

std::vector<uint8_t>& NDSFileByteArray::data() {
	return m_data;
}

void NDSFileByteArray::resize(size_t newSize) {
	m_data.resize(newSize);
}

void NDSFileByteArray::writeToFile(BinaryWriter& writer, size_t offset) const {
	writer.writeBytes(m_data, offset);
}

uint32_t NDSFileByteArray::size() const {
	return static_cast<uint32_t>(m_data.size());
}