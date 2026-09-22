#ifndef WCHAR_H
#define WCHAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef unsigned short wchar_t;

size_t wcslen(const wchar_t* s);
wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);
wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, size_t n);
int wcscmp(const wchar_t* s1, const wchar_t* s2);
int wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* WCHAR_H */
