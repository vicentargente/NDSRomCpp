#ifndef MODELCOMMANDBLOB_HPP
#define MODELCOMMANDBLOB_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "../../../../../file/NDSFile.hpp"

// TODO: Redo the class to interact with commands
class ModelCommandBlob {
public:
    ModelCommandBlob();
    ModelCommandBlob(std::shared_ptr<NDSFile> file, uint32_t offset, uint32_t size); // size in bytes
    
    void writeToNDSFile(std::shared_ptr<NDSFile> file, uint32_t offset);
private:
    std::vector<uint8_t> m_data;
};

#endif