#ifndef FILECOPIER_HPP
#define FILECOPIER_HPP

#include "./BinaryReader.hpp"
#include "./BinaryWriter.hpp"

class FileCopier {
public:
	FileCopier() {
		m_buffer = new char[BUFFER_SIZE];
	}
	~FileCopier() {
		delete[] m_buffer;
	};

	void copy(BinaryReader &reader, size_t rOffset, BinaryWriter &writer, size_t wOffset, size_t length) {
		while (length > 0) {
			size_t bytesToCopy = length > BUFFER_SIZE ? BUFFER_SIZE : length;
			reader.readBytes(m_buffer, bytesToCopy, rOffset);
			writer.writeBytes(m_buffer, bytesToCopy, wOffset);
			rOffset += bytesToCopy;
			wOffset += bytesToCopy;
			length -= bytesToCopy;
		}
	};
private:
	char* m_buffer;

	// Constants
	static const size_t BUFFER_SIZE = 0x20000; //128KB
};

#endif