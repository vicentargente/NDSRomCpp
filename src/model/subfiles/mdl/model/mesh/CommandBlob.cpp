#include "../../../../../../include/model/subfiles/mdl/model/mesh/CommandBlob.hpp"

ModelCommandBlob::ModelCommandBlob() : m_data(0) {

}

ModelCommandBlob::ModelCommandBlob(std::shared_ptr<NDSFile> file, uint32_t offset, uint32_t size) : m_data(size) {
    file->readBytes(m_data, offset);
}

void ModelCommandBlob::writeToNDSFile(std::shared_ptr<NDSFile> file, uint32_t offset) {
    file->writeBytes(m_data, offset);
}