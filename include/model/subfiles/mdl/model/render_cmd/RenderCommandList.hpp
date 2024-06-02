#ifndef MODELRENDERCOMMANDLIST_HPP
#define MODELRENDERCOMMANDLIST_HPP

#include <cstdint>
#include <vector>
#include <memory>

#include "RenderCommand.hpp"
#include "../../../../../file/NDSFile.hpp"

class ModelRenderCommandList {
public:
    ModelRenderCommandList(std::shared_ptr<NDSFile> file, uint32_t offset);

    ModelRenderCommand& operator[](size_t index) {
        return m_commands[index];
    }

    const ModelRenderCommand& operator[](size_t index) const {
        return m_commands[index];
    }

    uint32_t size() const;

    void writeToNdsFile(std::shared_ptr<NDSFile> file, uint32_t offset) const;
private:
    std::vector<ModelRenderCommand> m_commands;
    uint32_t m_size;
};

#endif