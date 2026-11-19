#ifndef REGREX_H
#define REGREX_H

#include <stddef.h>

typedef struct String {
  char *str;
  size_t len;
  size_t cap;
} string;

int concat_string(string *it, string *into, string *sep);

int copy_string(string *it, string *into);

int split_string(string *it, string *into, string *sep);

typedef struct Regex Regex;
typedef struct Regex {
  const char *pattern;
  int flags;
} Regex;

Regex *regex_compile(const string *pattern);
int regex_match(Regex *re, const string *text);

#endif // REGREX_H

#ifndef REGREX_IMPLEMENTATION

Regex *regex_compile(const string *pattern) {}

int regex_match(Regex *re, const string *text) {};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
