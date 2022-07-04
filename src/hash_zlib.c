#include <stdint.h>
#include <zlib.h>


uint32_t hash_crc32(char *buffer, size_t length) {
  uint32_t crc = crc32_z(0L, Z_NULL, 0);
  return crc32_z(crc, (Bytef *)buffer, length);
}


uint32_t hash_adler32(char *buffer, size_t length) {
  uint32_t adler = adler32_z(0L, Z_NULL, 0);
  return adler32_z(adler, (Bytef *)buffer, length);
}
