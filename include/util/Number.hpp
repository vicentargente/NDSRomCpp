#ifndef NDSNUMBER_HPP
#define NDSNUMBER_HPP

#include <cstdint>
#include <cstring>
#include <iostream>
#include <cmath>

class NdsFixedPoint1_19_12 {
public:
    NdsFixedPoint1_19_12() : m_value(0) {};
    explicit NdsFixedPoint1_19_12(uint32_t value) : m_value(static_cast<int32_t>(value)) {};
    explicit NdsFixedPoint1_19_12(double value) : m_value(doubleToFixed(value)) {};

    uint32_t getRaw() const {
        return m_value;
    };

    NdsFixedPoint1_19_12 operator+(const NdsFixedPoint1_19_12 &other) {
        return NdsFixedPoint1_19_12(static_cast<uint32_t>(m_value + other.m_value));
    };

    NdsFixedPoint1_19_12 operator-(const NdsFixedPoint1_19_12 &other) {
        return NdsFixedPoint1_19_12(static_cast<uint32_t>(m_value - other.m_value));
    }

    NdsFixedPoint1_19_12 operator*(const NdsFixedPoint1_19_12 &other) {
        return NdsFixedPoint1_19_12(
            static_cast<uint32_t>((static_cast<uint64_t>(m_value) * other.m_value) >> 12)
        );
    }

    NdsFixedPoint1_19_12 operator/(const NdsFixedPoint1_19_12 &other) {
        return NdsFixedPoint1_19_12(
            static_cast<uint32_t>((static_cast<uint64_t>(m_value) << 12) / other.m_value)
        );
    }

    bool operator==(const NdsFixedPoint1_19_12 &other) {
        return m_value == other.m_value;
    }

    double toDouble() const {
        int32_t const absmask = m_value >> 31;
        uint32_t valueAbs = (m_value + absmask) ^ absmask;

        uint8_t msb = __builtin_clz(valueAbs);

        uint32_t mask = ~static_cast<uint32_t>(static_cast<int32_t>(0x80000000) >> msb);

        uint32_t mantissa = valueAbs & mask;
        int16_t exponent = 1042 - msb; // 1042 = 1023 (exceso z de exp en double) + 19 (bits parte entera)

        uint64_t bits = 
            (static_cast<uint64_t>(m_value & 0x80000000) << 32) | // bit signo en posicion 31 hay que moverlo a la 63
            (static_cast<uint64_t>(exponent & 0x07FF) << 52) | // 52 (hay que saltarse la mantisa)
            (static_cast<uint64_t>(mantissa) << (21 + msb)); // 21 = 2 + 19 (bits parte entera)

        return *reinterpret_cast<double *>(&bits);
    }

    void fromDouble(double num) {
        m_value = doubleToFixed(num);
    }

private:
    int32_t m_value;

    static int32_t doubleToFixed(double num) {
        uint64_t bits = *reinterpret_cast<uint64_t*>(&num);

        bool isNegative = (bits & 0x8000000000000000) > 0;
        uint16_t exponent = ((bits & 0x7FF0000000000000) >> 52) - 1023;
        uint64_t mantissa = (bits & 0x000FFFFFFFFFFFFF) | 0x0010000000000000;

        uint32_t intMantissa = mantissa >> (40 - exponent);
        int32_t intPart = isNegative ? -intMantissa : intMantissa;

        return intPart;
    }
};

class NdsFixedPoint1_3_12 {
public:
    NdsFixedPoint1_3_12() : m_value(0) {};
    explicit NdsFixedPoint1_3_12(uint16_t value) : m_value(static_cast<int16_t>(value)) {};
    explicit NdsFixedPoint1_3_12(float value) : m_value(floatToFixed(value)) {};

        uint32_t getRaw() const {
        return m_value;
    };

    NdsFixedPoint1_3_12 operator+(const NdsFixedPoint1_3_12 &other) {
        return NdsFixedPoint1_3_12(static_cast<uint16_t>(m_value + other.m_value));
    };

    NdsFixedPoint1_3_12 operator-(const NdsFixedPoint1_3_12 &other) {
        return NdsFixedPoint1_3_12(static_cast<uint16_t>(m_value - other.m_value));
    }

    NdsFixedPoint1_3_12 operator*(const NdsFixedPoint1_3_12 &other) {
        return NdsFixedPoint1_3_12(
            static_cast<uint16_t>((static_cast<uint32_t>(m_value) * other.m_value) >> 12)
        );
    }

    NdsFixedPoint1_3_12 operator/(const NdsFixedPoint1_3_12 &other) {
        return NdsFixedPoint1_3_12(
            static_cast<uint16_t>((static_cast<uint32_t>(m_value) << 12) / other.m_value)
        );
    }

    bool operator==(const NdsFixedPoint1_3_12 &other) {
        return m_value == other.m_value;
    }

    float toFloat() const {
        int16_t const absmask = static_cast<int16_t>(m_value) >> 15;
        uint16_t valueAbs = (m_value + absmask) ^ absmask;

        uint8_t msb = __builtin_clz(valueAbs) - 16;

        uint16_t mask = ~static_cast<uint16_t>(static_cast<int16_t>(0x8000) >> msb);

        uint32_t mantissa = valueAbs & mask;
        int16_t exponent = 127 + 3 - msb;

        uint32_t bits = 
            (static_cast<uint32_t>(m_value & 0x8000) << 16) |
            (static_cast<uint32_t>(exponent & 0xFF) << 23) |
            (static_cast<uint32_t>(mantissa) << (8 + msb));

        return *reinterpret_cast<float *>(&bits);
    }

    void fromFloat(float num) {
        m_value = floatToFixed(num);
    }
private:
    uint16_t m_value;

    static uint16_t floatToFixed(float num) {
        uint32_t bits = *reinterpret_cast<uint32_t*>(&num);

        bool isNegative = (bits & 0x80000000) > 0;
        uint8_t exponent = ((bits & 0x7F800000) >> 23) - 127;
        uint32_t mantissa = (bits & 0x007FFFFF) | 0x00800000;

        uint16_t intMantissa = mantissa >> (11 - exponent);
        int16_t intPart = isNegative ? -intMantissa : intMantissa;

        return intPart;
    }
};

#endif