#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdlib.h>

typedef void U0;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef float F32;
typedef double F64;

typedef _Bool Bool;
#define FALSE 0
#define TRUE 1

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : -(a))

I64 power(I64 a, U64 b);

#endif