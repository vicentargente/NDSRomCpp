#ifndef MODELMESH_HPP
#define MODELMESH_HPP

#include <cstdint>
#include <memory>

#include "../../../../../file/NDSFile.hpp"
#include "CommandBlob.hpp"

class ModelMesh {
public:
    ModelMesh();
    ModelMesh(std::shared_ptr<NDSFile> file, uint32_t offset);

    uint16_t getDummy() const;
    uint16_t getSize() const;
    uint32_t getUnknown() const;
    uint32_t getCmdsOffset() const;
    uint32_t getCmdsLength() const;

    // TODO: Do operations with command blob when available

    void writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset);
private:
    uint16_t m_dummy;
    uint16_t m_size; // 16 always?
    uint32_t m_unknown;
    uint32_t m_cmdsOffset; // relative to this mesh
    uint32_t m_cmdsLength;
    // docs note: cmds_off points to a u8[cmds_len] blob containing the GPU commands.

    ModelCommandBlob m_commandBlob;
};


#endif