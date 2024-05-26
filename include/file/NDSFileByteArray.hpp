#ifndef NDSFILEBYTEARRAY_HPP
#define NDSFILEBYTEARRAY_HPP

#include "NDSFile.hpp"

class NDSFileByteArray : public NDSFile {
public:
	NDSFileByteArray(uint32_t fileSize);

	uint8_t readUInt8(size_t offset) const override;
	uint16_t readUInt16(size_t offset) const override;
	uint32_t readUInt32(size_t offset) const override;
	uint64_t readUInt64(size_t offset) const override;
	void readBytes(char *buffer, size_t size, size_t offset) const override;
	void readBytes(std::vector<uint8_t>& buffer, size_t offset) const override;

	void writeUInt8(size_t offset, uint8_t value) override;
	void writeUInt16(size_t offset, uint16_t value) override;
	void writeUInt32(size_t offset, uint32_t value) override;
	void writeUInt64(size_t offset, uint64_t value) override;
	void writeBytes(const std::vector<uint8_t>& buffer, size_t offset) override;

	void setContent(const std::vector<uint8_t>& content) override;
	void setContent(const char* filePath) override;

	void resize(size_t newSize) override;

	void writeToFile(BinaryWriter& writer, size_t offset) const override;
	uint32_t size() const override;

	std::vector<uint8_t>& data();

private:
	std::vector<uint8_t> m_data;
};

#endif