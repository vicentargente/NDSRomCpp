#ifndef NSBMD_HPP
#define NSBMD_HPP

#include <memory>
#include <vector>

#include "../../file/NDSFile.hpp"

#include "../common/Container.hpp"
#include "../subfiles/mdl/Mdl.hpp"
#include "../subfiles/tex/Tex.hpp"


class Nsbmd {
public:
    Nsbmd(std::shared_ptr<NDSFile> file);
private:
    ModelContainer m_container;
    std::vector<Mdl> m_mdls;
    std::vector<Tex> m_texs;

    static const uint32_t NSBMD_MAGIC;
};

#endif