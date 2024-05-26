#ifndef TEX_HPP
#define TEX_HPP

#include <cstdint>
#include <memory>

#include "../../../file/NDSFile.hpp"

class Tex {
public:
    Tex(std::shared_ptr<NDSFile> file, uint32_t offset);
private:
    uint32_t m_filesize;
};

#endif