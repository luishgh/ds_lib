#ifndef _DS_LIB_STRING_H
#define _DS_LIB_STRING_H

#include <stdlib.h>

/**
   Simple dynamic string implementation.

   For the time being, this doesn't have any small string optimizations.
 */

struct string {
  char* ptr;
  size_t size;
  size_t capacity;
};

// 15 chars + \0
#define STRING_STARTING_CAPACITY 16 

static inline void __string__realloc(struct string* str) {
  str->ptr = (char *) realloc(str->ptr, 2 * str->capacity);
  str->capacity = 2 * str->capacity;
}

static inline void __string_concat_ptr(struct string* str, char* ptr) {
  char * c = ptr;
  while (*c != '\0') {
    for (; str->size < str->capacity && *c != '\0'; c++, str->size++) {
      str->ptr[str->size] = *c;
    }

    if (str->size == str->capacity) __string__realloc(str);
  }

  str->ptr[str->size] = '\0';
}
static inline void __string_concat_ptr_sec(struct string* str, char* begin, char* end) {
  char * c = begin;
  while (c != end) {
    for (; str->size < str->capacity && c != end; c++, str->size++) {
      str->ptr[str->size] = *c;
    }

    if (str->size == str->capacity) __string__realloc(str);
  }

  str->ptr[str->size] = *end;
  if (str->size == str->capacity) __string__realloc(str);
  str->size++;
  str->ptr[str->size] = '\0';
}

static inline void string_initialize(struct string* str, char* content) {
  str->ptr = (char *) malloc(STRING_STARTING_CAPACITY);
  str->capacity = STRING_STARTING_CAPACITY;
  str->size = 0;
  __string_concat_ptr(str, content);
}

static inline void string_concat(struct string* dst, struct string* src) {
  __string_concat_ptr(dst, src->ptr);
}

static inline void string_append(struct string* dst, char* content) {
  __string_concat_ptr(dst, content);
}

static inline void string_clean(struct string *s) {
  s->size = 0;
  s->capacity = STRING_STARTING_CAPACITY;
  s->ptr = (char *) realloc(s->ptr, STRING_STARTING_CAPACITY);
  s->ptr[0] = '\0';
}

// TODO: support multiple whitespace delimeters
static inline int string_next_token(struct string* s, struct string* token, int pos) {
  string_clean(token);

  char *c = &s->ptr[pos];

  // Jump to next valid char
  while (*c == ' ') {
    c++;
  }

  char *begin = c;

  while (*c != ' ' && *c != '\0') {
    c++;
  }

  char *end = --c;

  __string_concat_ptr_sec(token, begin, end);

  return end - s->ptr + 1;
}

static inline void string_destroy(struct string* s) {
  free(s->ptr);
}

#endif /* _DS_LIB_STRING_H */
