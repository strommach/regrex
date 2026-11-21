#ifndef REGREX_H
#define REGREX_H

#include <stddef.h>

typedef char *string;

typedef struct Regex Regex;
typedef struct Regex {
  const string pattern;
  int flags;
} Regex;

Regex *regex_compile(const string pattern);
int regex_match(Regex *re, const string text);

#endif // REGREX_H

#ifndef REGREX_IMPLEMENTATION

Regex *regex_compile(const string pattern) {}

int regex_match(Regex *re, const string text) {};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
