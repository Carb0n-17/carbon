#include "png/crc.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static uint32_t crc_table[256];
static bool crc_table_computed = false;

static void make_crc_table(void)
{
    for (uint_fast16_t i = 0; i < 256; i++) {
        uint32_t c = i;
        for (uint_fast8_t j = 0; j < 8; j++) {
            c = (c & 1) ? (0xEDB88320U ^ (c >> 1)) : (c >> 1);
        }
        crc_table[i] = c;
    }
    crc_table_computed = true;
}

uint32_t update_crc(uint32_t crc, const uint8_t *buf, const size_t len)
{
    if (!crc_table_computed) {
        make_crc_table();
    }

    for (size_t i = 0; i < len; i++) {
        crc = crc_table[(crc ^ buf[i]) & 0xFF] ^ (crc >> 8);
    }

    return crc;
}

uint32_t crc(const uint8_t *buf, const size_t len)
{
    return update_crc(0xFFFFFFFFU, buf, len) ^ 0xFFFFFFFFU;
}