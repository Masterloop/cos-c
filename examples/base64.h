#ifndef BASE64_H

#include <stddef.h>
#include <stdint.h>

size_t base64_encode(uint8_t *const out, const uint8_t *src, size_t len);
size_t base64_enc_len(size_t plainLen);

size_t base64_decode(uint8_t *const out, const uint8_t *src, size_t len);
size_t base64_dec_len(const uint8_t *const data, size_t len);

#define BASE64_H
#endif