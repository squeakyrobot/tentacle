#include "util.h"

uint32_t normalizeRange(uint32_t value, uint32_t min, uint32_t max, uint32_t inMin, uint32_t inMax) {
    return (value - inMin) * (max - min) / (inMax - inMin) + min;
}