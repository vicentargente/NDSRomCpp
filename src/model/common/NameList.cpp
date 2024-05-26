#include "../../../include/model/common/NameList.hpp"

// template <typename T>
// ModelNameList<T>::ModelNameList(std::shared_ptr<NDSFile> file, uint32_t offset) :
//     m_dummy(file->readUInt8(offset)),
//     m_count(file->readUInt8(offset + 1)),
//     m_size(file->readUInt16(offset + 2)),
//     m_unknown {
//         file->readUInt16(offset + 4),
//         file->readUInt16(offset + 6),
//         file->readUInt32(offset + 8),
//         std::vector<uint32_t>(m_count) //offset + 12
//     },
//     m_elementSize(file->readUInt16(offset + 12 + m_count * sizeof(uint32_t))),
//     m_dataSectionSize(file->readUInt16(offset + 14 + m_count * sizeof(uint32_t))),
//     m_data(m_count), //offset + 16 + m_count * sizeof(uint32_t)
//     m_names(m_count) //offset + 20 + 2 * (m_count * sizeof(uint32_t))
// {
//     // Initialize unknown.unknown2
//     std::vector<uint32_t> &unknown2 = m_unknown.unknown2;
//     for (uint16_t i = 0; i < m_count; i++) {
//         unknown2[i] = file->readUInt32(offset + 12 + i * sizeof(uint32_t));
//     }

//     // Initialize data
//     for (uint16_t i = 0; i < m_count; i++) {
//         m_data[i] = file->readUInt32(offset + 14 + m_count * sizeof(uint32_t) + i * sizeof(uint32_t));
//     }
// }