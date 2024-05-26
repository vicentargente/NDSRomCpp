#include "../../../include/model/files/Nsbmd.hpp"

const uint32_t Nsbmd::NSBMD_MAGIC = 0x30444D42;

Nsbmd::Nsbmd(std::shared_ptr<NDSFile> file) : m_container(file), m_mdls(), m_texs() {
    if (m_container.getType() != NSBMD_MAGIC) {
        throw std::runtime_error("File is not a NSBMD file");
    }

    const std::vector<uint32_t> &subFileOffsets = m_container.getSubfileOffsets();

    for (uint32_t offset : subFileOffsets) {
        uint32_t magic = file->readUInt32(offset) & 0x00FFFFFF;

        switch (magic) {
            case 0x4C444D:
                m_mdls.push_back(Mdl(file, offset));
                break;
            case 0x584554:
                m_texs.push_back(Tex(file, offset));
                break;
        }
    }
}