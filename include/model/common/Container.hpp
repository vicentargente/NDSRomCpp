#ifndef MODELCONTAINER_HPP
#define MODELCONTAINER_HPP

#include "../../file/NDSFile.hpp"

#include <memory>
#include <cstdint>

class ModelContainer {
enum class ModelFileType: uint32_t {
    NSBMD = 0x30444D42, // 'BMD0'
    NSBTX = 0x30585442, // 'BTX0'
    NSBCA = 0x30414342, // 'BCA0'
    NSBTP = 0x30505442, // 'BPT0'
    NSBTA = 0x30415442  // 'BTA0'
};

public:
    ModelContainer(std::shared_ptr<NDSFile> file);
    uint32_t getType() const;

    uint16_t getByteOrderMark() const;
    void setByteOrderMark(uint16_t value);

    uint16_t getVersion() const;
    void setVersion(uint16_t value);

    uint32_t getFileSize() const;
    void setFileSize(uint32_t value);

    uint16_t getHeaderSize() const;

    uint16_t getNumSubfiles() const;

    std::vector<uint32_t> getSubfileOffsets() const;
    void addSubfileOffset(uint32_t offset);
    void removeSubfileOffset(uint32_t index);
private:
    //Header attributes
    uint32_t m_type;
    uint16_t m_byteOrderMark;
    uint16_t m_version;
    uint32_t m_fileSize;
    uint16_t m_headerSize;
    uint16_t m_numSubfiles;
    //End header attributes

    std::vector<uint32_t> m_subfileOffsets;
};

#endif