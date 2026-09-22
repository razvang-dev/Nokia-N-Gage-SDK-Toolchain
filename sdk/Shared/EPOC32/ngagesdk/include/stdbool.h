#ifndef STDBOOL_H
#define STDBOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef bool
#define bool unsigned char
#endif

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif

#ifdef __cplusplus
}
#endif

#endif /* STDBOOL_H */
