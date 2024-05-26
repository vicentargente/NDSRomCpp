#include "../../../include/model/common/Container.hpp"

ModelContainer::ModelContainer(std::shared_ptr<NDSFile> file):
    m_type(file->readUInt32(0)),
    m_byteOrderMark(file->readUInt16(4)),
    m_version(file->readUInt16(6)),
    m_fileSize(file->readUInt32(8)),
    m_headerSize(file->readUInt16(12)),
    m_numSubfiles(file->readUInt16(14)),
    m_subfileOffsets(m_numSubfiles)
{
    switch (m_type) {
        case static_cast<uint32_t>(ModelFileType::NSBMD):
        case static_cast<uint32_t>(ModelFileType::NSBTX):
        case static_cast<uint32_t>(ModelFileType::NSBCA):
        case static_cast<uint32_t>(ModelFileType::NSBTP):
        case static_cast<uint32_t>(ModelFileType::NSBTA):
            break;
        default:
            throw std::runtime_error("Invalid model file type");
    }

    for (uint16_t i = 0; i < m_numSubfiles; i++) {
        m_subfileOffsets[i] = file->readUInt32(16 + (i << 2));
    }
}

uint32_t ModelContainer::getType() const {
    return m_type;
}

uint16_t ModelContainer::getByteOrderMark() const {
    return m_byteOrderMark;
}

void ModelContainer::setByteOrderMark(uint16_t byteOrderMark) {
    m_byteOrderMark = byteOrderMark;
}

uint16_t ModelContainer::getVersion() const {
    return m_version;
}

void ModelContainer::setVersion(uint16_t version) {
    m_version = version;
}

uint32_t ModelContainer::getFileSize() const {
    return m_fileSize;
}

void ModelContainer::setFileSize(uint32_t fileSize) {
    m_fileSize = fileSize;
}

uint16_t ModelContainer::getHeaderSize() const {
    return m_headerSize;
}

uint16_t ModelContainer::getNumSubfiles() const {
    return m_numSubfiles;
}

std::vector<uint32_t> ModelContainer::getSubfileOffsets() const {
    return m_subfileOffsets;
}

void ModelContainer::addSubfileOffset(uint32_t offset) {
    m_numSubfiles++;
    m_subfileOffsets.push_back(offset);
}

void ModelContainer::removeSubfileOffset(uint32_t index) {
    m_numSubfiles--;
    m_subfileOffsets.erase(m_subfileOffsets.begin() + index);
}