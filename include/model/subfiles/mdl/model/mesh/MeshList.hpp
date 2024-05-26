#ifndef MODELMESHLIST_HPP
#define MODELMESHLIST_HPP

#include <cstdint>
#include <vector>
#include <memory>

#include "../../../../common/NameList.hpp"
#include "../../../../../file/NDSFile.hpp"
#include "Mesh.hpp"

class ModelMeshList {
public:
    ModelMeshList(std::shared_ptr<NDSFile> file, uint32_t offset, uint8_t numMeshes);
private:
    ModelNameList<uint32_t> m_meshList;
    std::vector<ModelMesh> m_meshes;
};

#endif