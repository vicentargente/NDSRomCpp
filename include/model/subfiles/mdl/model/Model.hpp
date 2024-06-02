#ifndef MDLMODEL_HPP
#define MDLMODEL_HPP

#include <memory>
#include <cstdint>

#include "../../../../file/NDSFile.hpp"
#include "../../../../util/Number.hpp"

#include "mesh/MeshList.hpp"
#include "render_cmd/RenderCommandList.hpp"

// #include "../../../common/NameList.hpp"

class MdlModel {
    #pragma region structs
    struct BoundingBox {
        NdsFixedPoint1_3_12 xMin;
        NdsFixedPoint1_3_12 yMin;
        NdsFixedPoint1_3_12 zMin;

        NdsFixedPoint1_3_12 xMax;
        NdsFixedPoint1_3_12 yMax;
        NdsFixedPoint1_3_12 zMax;
    };

    #pragma endregion
public:
    MdlModel(std::shared_ptr<NDSFile> file, uint32_t offset);
private:
    uint32_t m_fileSize;

    // All offsets relative to this Model
    uint32_t m_renderCmdsOffset;
    uint32_t m_materialsOffset;
    uint32_t m_meshesOffset;
    uint32_t m_invBindsOffset;

    uint8_t m_unknown1;
    uint8_t m_unknown2;
    uint8_t m_unknown3;
    uint8_t m_numBoneMatrices;
    uint8_t m_numMaterials;
    uint8_t m_numMeshes;
    uint8_t m_unknown4;
    uint8_t m_unknown5;

    NdsFixedPoint1_19_12 m_upScale;
    NdsFixedPoint1_19_12 m_downScale;

    uint16_t m_numVertices;
    uint16_t m_numPolygons; // num tris + num quads?
    uint16_t m_numTris;
    uint16_t m_numQuads;

    BoundingBox m_boundingBox;

    uint8_t m_unknown6[8];

    // TODO: BoneList

    ModelRenderCommandList m_renderCmdList; // Pointed by m_renderCmdsOffset
    ModelMeshList m_meshList; // Pointed by m_meshesOffset
};

#endif