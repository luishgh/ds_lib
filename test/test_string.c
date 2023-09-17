#include <stdio.h>

#include "../include/ds_lib/string.h"

int main() {

  struct string s;

  string_initialize(&s, "alvongas");

  printf("%s\n", s.ptr);

  string_append(&s, " gostoso!");

  printf("%s %zu %zu\n", s.ptr, s.size, s.capacity);

  int pos = 0;
  struct string token;
  string_initialize(&token, "");
  while (pos != s.size) {
    pos = string_next_token(&s, &token, pos);
    printf("Token: %s\n", token.ptr);
  }

  string_destroy(&s);
  
  return 0;
}
