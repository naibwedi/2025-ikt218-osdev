#pragma once

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Correct size_t for 32-bit kernel (long unsigned int)
typedef uint32_t size_t;
