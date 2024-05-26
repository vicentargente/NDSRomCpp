#include "../../../../../../include/model/subfiles/mdl/model/mesh/MeshList.hpp"

ModelMeshList::ModelMeshList(std::shared_ptr<NDSFile> file, uint32_t offset, uint8_t numMeshes) :
    m_meshList(file, offset),
    m_meshes(numMeshes)
{
    std::vector<uint32_t> &meshOffsets = m_meshList.getDataRef();
    for (uint8_t i = 0; i < meshOffsets.size(); i++) {
        m_meshes[i] = ModelMesh(file, offset + meshOffsets[i]);
    }
}