#ifndef MODELNAME_HPP
#define MODELNAME_HPP

#include <cstring>

struct ModelName {
    char data[16];

    ModelName() {
        std::memset(data, 0, sizeof(data));
    }

    ModelName(const char* str) {
        std::strncpy(data, str, sizeof(data));
    }

    // Operador de acceso para conveniencia
    char& operator[](size_t index) {
        return data[index];
    }

    const char& operator[](size_t index) const {
        return data[index];
    }
};

#endif