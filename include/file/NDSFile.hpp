#ifndef NDSFILE_HPP
#define NDSFILE_HPP

#include <cstdint>
#include <vector>

#include "../util/BinaryWriter.hpp"

class NDSFile {
public:
	virtual uint8_t readUInt8(size_t offset) const = 0;
	virtual uint16_t readUInt16(size_t offset) const = 0;
	virtual uint32_t readUInt32(size_t offset) const = 0;
	virtual uint64_t readUInt64(size_t offset) const = 0;
	virtual void readBytes(std::vector<uint8_t>& buffer, size_t offset) const = 0;

	virtual void writeUInt8(size_t offset, uint8_t value) = 0;
	virtual void writeUInt16(size_t offset, uint16_t value) = 0;
	virtual void writeUInt32(size_t offset, uint32_t value) = 0;
	virtual void writeUInt64(size_t offset, uint64_t value) = 0;
	virtual void writeBytes(const std::vector<uint8_t>& buffer, size_t offset) = 0;

	virtual void setContent(const std::vector<uint8_t>& content) = 0;
	virtual void setContent(const char* filePath) = 0;

	virtual void resize(size_t newSize) = 0;

	virtual void writeToFile(BinaryWriter& writer, size_t offset) const = 0;
	virtual uint32_t size() const = 0;

	virtual ~NDSFile() = default;
};

#endif