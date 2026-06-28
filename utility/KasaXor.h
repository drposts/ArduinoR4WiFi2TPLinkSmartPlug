#pragma once
#include <stdint.h>
#include <stddef.h>

inline void kasaXor(uint8_t* data, size_t len) {
    uint8_t key = 0xAB;
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key;
        key = data[i];
    }
}
