#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#define ISVALIDSOCKET(x) (x > 0)

#include <stdint.h>
#include <stddef.h>

#define ERRORPRINT(_fmt, ...) fprintf(stderr, "ERROR: " _fmt, __VA_ARGS__);

#pragma pack(1)
typedef struct header
{
    uint32_t magic_number;
    size_t size;
} header_t;

enum {BUFFSZ = 512};
typedef enum {NETWORK, HOST} endianess_t;
typedef enum{READ_ERROR, INVALID_SOCKET, CONVERSION_ERROR, OK, INVALID_MAGIC_NUMBER} errors_t;

int convert_header_to(header_t * header, endianess_t endianess);

#endif