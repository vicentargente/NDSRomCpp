#ifndef MODELNAMELIST_HPP
#define MODELNAMELIST_HPP

#include <cstdint>
#include <vector>
#include <memory>
#include <concepts>

#include "Name.hpp"
#include "../../file/NDSFile.hpp"

template <typename T>
concept HasWriteToBuffer = requires(T t, std::vector<uint8_t> &buffer, uint32_t offset) {
    { t.writeToBuffer(buffer, offset) } -> std::same_as<void>;
    { T::size() } -> std::same_as<uint32_t>;
};

template <typename T>
concept ValidType = std::same_as<T, uint32_t> || HasWriteToBuffer<T>;

template <ValidType T>
class ModelNameList {
    struct Unknown {
        // Header
        uint16_t subheaderSize; // Size of Unknown header
        uint16_t unknownSize; // Size of Unknown
        uint32_t unknown1;
        // End header
        
        std::vector<uint32_t> unknown2;
    };

public:
    ModelNameList(std::shared_ptr<NDSFile> file, uint32_t offset);

    uint8_t getDummy() const;
    uint8_t getCount() const;
    uint16_t getSize() const;
    // TODO: Get unknown params?
    uint16_t getElementSize() const;
    uint16_t getDataSectionSize() const;
    std::vector<T> getData() const;
    std::vector<T> &getDataRef();
    std::vector<ModelName> getNames() const;
    std::vector<ModelName> &getNamesRef();

    void writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset) const;
private:
    uint8_t m_dummy;
    uint8_t m_count; // Number of elements
    uint16_t m_size; // NameList size in bytes
    Unknown m_unknown;
    uint16_t m_elementSize; // sizeof(T)
    uint16_t m_dataSectionSize;
    std::vector<T> m_data;
    std::vector<ModelName> m_names;
};

template <ValidType T>
ModelNameList<T>::ModelNameList(std::shared_ptr<NDSFile> file, uint32_t offset) :
    m_dummy(file->readUInt8(offset)),
    m_count(file->readUInt8(offset + 1)),
    m_size(file->readUInt16(offset + 2)),
    m_unknown {
        file->readUInt16(offset + 4),
        file->readUInt16(offset + 6),
        file->readUInt32(offset + 8),
        std::vector<uint32_t>(m_count) //offset + 12
    },
    m_elementSize(file->readUInt16(offset + 12 + m_count * sizeof(uint32_t))),
    m_dataSectionSize(file->readUInt16(offset + 14 + m_count * sizeof(uint32_t))),
    m_data(m_count),
    m_names(m_count)
{
    uint16_t baseOffset;

    // Initialize unknown.unknown2
    std::vector<uint32_t> &unknown2 = m_unknown.unknown2;
    baseOffset = offset + 12;
    for (uint16_t i = 0; i < m_count; i++) {
        unknown2[i] = file->readUInt32(baseOffset + i * sizeof(uint32_t));
    }

    // Initialize data
    baseOffset = offset + 16 + m_count * sizeof(uint32_t);
    for (uint16_t i = 0; i < m_count; i++) {
        m_data[i] = file->readUInt32(baseOffset + i * sizeof(uint32_t));
    }

    // Initialize names
    baseOffset = offset + 16 + 2 * (m_count * sizeof(uint32_t));
    file->readBytes(reinterpret_cast<char *>(m_names.data()), m_count * 16, baseOffset);
}

template <ValidType T>
uint8_t ModelNameList<T>::getDummy() const {
    return m_dummy;
}

template <ValidType T>
uint8_t ModelNameList<T>::getCount() const {
    return m_count;
}

template <ValidType T>
uint16_t ModelNameList<T>::getSize() const {
    return m_size;
}

// Get unknown params here

template <ValidType T>
uint16_t ModelNameList<T>::getElementSize() const {
    return m_elementSize;
}

template <ValidType T>
uint16_t ModelNameList<T>::getDataSectionSize() const {
    return m_dataSectionSize;
}

template <ValidType T>
std::vector<T> ModelNameList<T>::getData() const {
    return m_data;
}

template <ValidType T>
std::vector<T> &ModelNameList<T>::getDataRef() {
    return m_data;
}

template <ValidType T>
std::vector<ModelName> ModelNameList<T>::getNames() const {
    return m_names;
}

template <ValidType T>
std::vector<ModelName> &ModelNameList<T>::getNamesRef() {
    return m_names;
}

template <ValidType T>
void ModelNameList<T>::writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset) const {
    if constexpr (std::is_same_v<T, uint32_t>) {
        std::vector<uint8_t> buffer(16 + m_count * 24);
        uint16_t baseOffset = 12;

        buffer[0] = m_dummy;
        buffer[1] = m_count;
        *reinterpret_cast<uint16_t*>(&buffer[2]) = m_size;
        *reinterpret_cast<uint16_t*>(&buffer[4]) = m_unknown.subheaderSize;
        *reinterpret_cast<uint16_t*>(&buffer[6]) = m_unknown.unknownSize;
        *reinterpret_cast<uint32_t*>(&buffer[8]) = m_unknown.unknown1;
        for (uint8_t i = 0; i < m_count; i++) {
            *reinterpret_cast<uint32_t*>(&buffer[baseOffset]) = m_unknown.unknown2[i];
            baseOffset += 4;
        }
        *reinterpret_cast<uint16_t*>(&buffer[baseOffset]) = m_elementSize;
        *reinterpret_cast<uint16_t*>(&buffer[baseOffset + 2]) = m_dataSectionSize;
        baseOffset += 4;
        for (uint8_t i = 0; i < m_count; i++) {
            *reinterpret_cast<uint32_t*>(&buffer[baseOffset]) = m_data[i];
            baseOffset += 4;
        }
        for (uint8_t i = 0; i < m_count; i++) {
            for (uint8_t j = 0; j < 16; j += 8) {
                *reinterpret_cast<uint64_t*>(&buffer[baseOffset]) = *reinterpret_cast<const uint64_t*>(&m_names[i][j]);
                baseOffset+=8;
            }
        }

        file->writeBytes(buffer, offset);
    }
    else {
        std::vector<uint8_t> buffer(16 + m_count * (20 + T::size()));
        uint16_t baseOffset = 12;

        buffer[0] = m_dummy;
        buffer[1] = m_count;
        *reinterpret_cast<uint16_t*>(&buffer[2]) = m_size;
        *reinterpret_cast<uint16_t*>(&buffer[4]) = m_unknown.subheaderSize;
        *reinterpret_cast<uint16_t*>(&buffer[6]) = m_unknown.unknownSize;
        *reinterpret_cast<uint32_t*>(&buffer[8]) = m_unknown.unknown1;
        for (uint8_t i = 0; i < m_count; i++) {
            *reinterpret_cast<uint32_t*>(&buffer[baseOffset]) = m_unknown.unknown2[i];
            baseOffset += 4;
        }
        *reinterpret_cast<uint16_t*>(&buffer[baseOffset]) = m_elementSize;
        *reinterpret_cast<uint16_t*>(&buffer[baseOffset + 2]) = m_dataSectionSize;
        baseOffset += 4;
        for (uint8_t i = 0; i < m_count; i++) {
            m_data[i].writeToBuffer(buffer, baseOffset);
            baseOffset += m_data[i].size();
        }
        for (uint8_t i = 0; i < m_count; i++) {
            for (uint8_t j = 0; j < 16; j += 8) {
                *reinterpret_cast<uint64_t*>(&buffer[baseOffset]) = *reinterpret_cast<const uint64_t*>(&m_names[i][j]);
                baseOffset+=8;
            }
        }

        file->writeBytes(buffer, offset);
    }
}

#endif

