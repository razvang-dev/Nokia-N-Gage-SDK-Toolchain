#ifndef INTTYPES_H
#define INTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/* Format specifiers for printf and scanf */

/* Integer types */
#define PRId8  "d"
#define PRIi8  "i"
#define PRId16 "d"
#define PRIi16 "i"
#define PRId32 "d"
#define PRIi32 "i"
#define PRId64 "lld"
#define PRIi64 "lli"

#define PRIo8  "o"
#define PRIu8  "u"
#define PRIx8  "x"
#define PRIX8  "X"

#define PRIo16 "o"
#define PRIu16 "u"
#define PRIx16 "x"
#define PRIX16 "X"

#define PRIo32 "o"
#define PRIu32 "u"
#define PRIx32 "x"
#define PRIX32 "X"

#define PRIo64 "llo"
#define PRIu64 "llu"
#define PRIx64 "llx"
#define PRIX64 "llX"

/* Scanf format specifiers */
#define SCNd8  "hhd"
#define SCNi8  "hhi"
#define SCNd16 "hd"
#define SCNi16 "hi"
#define SCNd32 "d"
#define SCNi32 "i"
#define SCNd64 "lld"
#define SCNi64 "lli"

#define SCNo8  "hho"
#define SCNu8  "hhu"
#define SCNx8  "hhx"

#define SCNo16 "ho"
#define SCNu16 "hu"
#define SCNx16 "hx"

#define SCNo32 "o"
#define SCNu32 "u"
#define SCNx32 "x"

#define SCNo64 "llo"
#define SCNu64 "llu"
#define SCNx64 "llx"

/* Greatest-width integer format specifiers */
#define PRIdMAX PRId64
#define PRIiMAX PRIi64
#define PRIoMAX PRIo64
#define PRIuMAX PRIu64
#define PRIxMAX PRIx64
#define PRIXMAX PRIX64

#define SCNdMAX SCNd64
#define SCNiMAX SCNi64
#define SCNoMAX SCNo64
#define SCNuMAX SCNu64
#define SCNxMAX SCNx64

/* intptr_t and uintptr_t format specifiers */
#define PRIdPTR PRId32
#define PRIiPTR PRIi32
#define PRIoPTR PRIo32
#define PRIuPTR PRIu32
#define PRIxPTR PRIx32
#define PRIXPTR PRIX32

#define SCNdPTR SCNd32
#define SCNiPTR SCNi32
#define SCNoPTR SCNo32
#define SCNuPTR SCNu32
#define SCNxPTR SCNx32

#ifdef __cplusplus
}
#endif

#endif /* INTTYPES_H */
