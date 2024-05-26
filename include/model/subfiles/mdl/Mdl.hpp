#ifndef MDL_HPP
#define MDL_HPP

#include <cstdint>
#include <memory>

#include "../../common/NameList.hpp"
#include "../../../file/NDSFile.hpp"

class Mdl {
public:
    Mdl(std::shared_ptr<NDSFile> file, uint32_t offset);
private:
    uint32_t m_stamp;
    uint32_t m_fileSize;
    ModelNameList<uint32_t> m_models; // Model offsets from this mdl
};

#endif