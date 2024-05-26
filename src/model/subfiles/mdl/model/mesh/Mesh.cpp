#include "../../../../../../include/model/subfiles/mdl/model/mesh/Mesh.hpp"

ModelMesh::ModelMesh() : m_commandBlob()
{

}

ModelMesh::ModelMesh(std::shared_ptr<NDSFile> file, uint32_t offset) :
    m_dummy(file->readUInt16(offset)),
    m_size(file->readUInt16(offset + 2)),
    m_unknown(file->readUInt32(offset + 4)),
    m_cmdsOffset(file->readUInt32(offset + 8)),
    m_cmdsLength(file->readUInt32(offset + 12)),
    m_commandBlob(file, offset + m_cmdsOffset, m_cmdsLength)
{

}

void ModelMesh::writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset) {
    std::vector<uint8_t> buffer(16);

    *reinterpret_cast<uint16_t *>(&buffer[0]) = m_dummy;
    *reinterpret_cast<uint16_t *>(&buffer[2]) = m_size;
    *reinterpret_cast<uint32_t *>(&buffer[4]) = m_unknown;
    *reinterpret_cast<uint32_t *>(&buffer[8]) = m_cmdsOffset;
    *reinterpret_cast<uint32_t *>(&buffer[12]) = m_cmdsLength;

    file->writeBytes(buffer, offset);

    m_commandBlob.writeToNDSFile(file, offset + m_cmdsOffset);
}

uint16_t ModelMesh::getDummy() const {
    return m_dummy;
}

uint16_t ModelMesh::getSize() const {
    return m_size;
}

uint32_t ModelMesh::getUnknown() const {
    return m_unknown;
}

uint32_t ModelMesh::getCmdsOffset() const {
    return m_cmdsOffset;
}

uint32_t ModelMesh::getCmdsLength() const {
    return m_cmdsLength;
}