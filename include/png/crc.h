#ifndef CRC_H
#define CRC_H

#include <stddef.h>
#include <stdint.h>

uint32_t update_crc(uint32_t crc, const uint8_t *buf, const size_t len);
uint32_t crc(const uint8_t *buf, const size_t len);

#endif // CRC_H