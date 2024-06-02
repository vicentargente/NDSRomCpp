#ifndef MODELRENDERCOMMAND_HPP
#define MODELRENDERCOMMAND_HPP

#include <cstdint>
#include <memory>

#include "../../../../../file/NDSFile.hpp"

class ModelRenderCommand {
public:
    ModelRenderCommand();
    ModelRenderCommand(const ModelRenderCommand &other);
    ModelRenderCommand(std::shared_ptr<NDSFile> file, uint32_t offset);

    ~ModelRenderCommand();

    uint8_t size() const; // command + num_params in bytes
    uint8_t numParams() const;
    uint8_t cmd() const;
    uint8_t *params() const;

    void writeToBuffer(std::vector<uint8_t> &buffer, uint32_t offset) const;
private:
    uint8_t m_cmd;
    uint8_t m_numParams;
    uint8_t *m_params;

    static uint8_t getNumParams(uint8_t cmd, const std::shared_ptr<NDSFile> &file, uint32_t offset);
};

#endif