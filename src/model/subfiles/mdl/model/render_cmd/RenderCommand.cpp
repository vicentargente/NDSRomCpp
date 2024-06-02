#include "../../../../../../include/model/subfiles/mdl/model/render_cmd/RenderCommand.hpp"
#include <stdexcept>
#include <string>

ModelRenderCommand::ModelRenderCommand() :
    m_cmd(0),
    m_numParams(0),
    m_params(nullptr)
{

}

ModelRenderCommand::ModelRenderCommand(const ModelRenderCommand & other) :
    m_cmd(other.m_cmd),
    m_numParams(other.m_numParams),
    m_params(new uint8_t[m_numParams])
{
    for (uint8_t i = 0; i < m_numParams; i++) {
        m_params[i] = other.m_params[i];
    }
}

ModelRenderCommand::ModelRenderCommand(std::shared_ptr<NDSFile> file, uint32_t offset) :
    m_cmd(file->readUInt8(offset)),
    m_numParams(getNumParams(m_cmd, file, offset)),
    m_params(new uint8_t[m_numParams])
{
    file->readBytes(reinterpret_cast<char *>(m_params), m_numParams, offset + 1);
}

ModelRenderCommand::~ModelRenderCommand() {
    delete [] m_params;
}

uint8_t ModelRenderCommand::size() const {
    return m_numParams + 1;
}

uint8_t ModelRenderCommand::numParams() const {
    return m_numParams;
}

uint8_t ModelRenderCommand::cmd() const {
    return m_cmd;
}

uint8_t *ModelRenderCommand::params() const {
    return m_params;
}

void ModelRenderCommand::writeToBuffer(std::vector<uint8_t> &buffer, uint32_t offset) const {
    buffer[offset] = m_cmd;
    for (uint8_t i = 0; i < m_numParams; i++) {
        buffer[offset + i + 1] = m_params[i];
    }
}

uint8_t ModelRenderCommand::getNumParams(uint8_t cmd, const std::shared_ptr<NDSFile> &file, uint32_t offset) {
    switch(cmd) {
        case 0x00: // Nop
        case 0x40: // Nop
        case 0x80: // Nop
        case 0x01: // End
        case 0x0B: // Scale Up
        case 0x2B: // Scale Down
            return 0;
        case 0x03: // Load Matrix from Stack
        case 0x04: // Bind Material
        case 0x24: // Bind Material
        case 0x44: // Bind Material
        case 0x05: // Draw Mesh
        case 0x07: // Unknown
        case 0x47: // Unknown
        case 0x08: // Unknown
            return 1;
        case 0x02: // Unknown
        case 0x0C: // Unknown
        case 0x0D: // Unknown
            return 2;
        case 0x06: // Multiply Current Matrix with Bone Matrix 
            return 3;
        case 0x26: // Multiply Current Matrix with Bone Matrix 
        case 0x46: // Multiply Current Matrix with Bone Matrix 
            return 4;
        case 0x66: // Multiply Current Matrix with Bone Matrix 
            return 5;
        case 0x09:
            return 1 + file->readUInt8(offset + 1);
        default:
            throw std::runtime_error(std::string("Unknown Render Command: ") + std::to_string(cmd));
    }
}