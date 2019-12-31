#ifdef __STDC_WANT_LIB_EXT1__
#undef __STDC_WANT_LIB_EXT1__
#endif
#define __STDC_WANT_LIB_EXT1__ 1
#ifdef UNICODE
typedef wchar_t uchar;
#include<wchar.h>
#define ustrnlen_s wcsnlen_s
#define ustrcpy_s wcscpy_s
#defie ustrcmp wcscmp
#else
typedef char uchar;
#include<string.h>
#define ustrnlen_s strnlen_s
#define ustrcpy_s strcpy_s
#defie ustrcmp strcmp
#endif
