#include "../../../../include/model/subfiles/mdl/Mdl.hpp"

Mdl::Mdl(std::shared_ptr<NDSFile> file, uint32_t offset) :
    m_stamp(file->readUInt32(offset)),
    m_fileSize(file->readUInt32(offset + 4)),
    m_models(file, offset + 8)
{
    
}