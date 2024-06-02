#include "../../../../../../include/model/subfiles/mdl/model/render_cmd/RenderCommandList.hpp"

ModelRenderCommandList::ModelRenderCommandList(std::shared_ptr<NDSFile> file, uint32_t offset) {
    uint32_t i = static_cast<uint32_t>(-1);
    uint32_t cmdOffset = offset;

    do {
        i++;
        m_commands.emplace_back(file, cmdOffset);
        cmdOffset += m_commands[i].size();
    } while(m_commands[i].cmd() != 0x01);

    m_size = cmdOffset - offset;
}

void ModelRenderCommandList::writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset) const {
    uint8_t cmdOffset = 0;
    std::vector<uint8_t> buffer(m_size);
    for (const ModelRenderCommand &command : m_commands) {
        command.writeToBuffer(buffer, cmdOffset);
    }
    
    file->writeBytes(buffer, offset);
}

uint32_t ModelRenderCommandList::size() const {
    return m_size;
}