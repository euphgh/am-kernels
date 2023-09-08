#include "trap.h"

int main() {
  char one[21], two[21];
  check(memcmp("a", "a", 1) == 0);      /* Identity. */
  check(memcmp("abc", "abc", 3) == 0);  /* Multicharacter. */
  check(memcmp("abcd", "abcf", 4) < 0); /* Honestly unequal. */
  check(memcmp("abcf", "abcd", 4) > 0);
  check(memcmp("alph", "cold", 4) < 0);
  check(memcmp("a\203", "a\003", 2) > 0);
  check(memcmp("a\003", "a\203", 2) < 0);
  check(memcmp("a\003bc", "a\203bc", 2) < 0);
  check(memcmp("abc\203", "abc\003", 4) > 0);
  check(memcmp("abc\003", "abc\203", 4) < 0);
  check(memcmp("abcf", "abcd", 3) == 0); /* Count limited. */
  check(memcmp("abc", "def", 0) == 0);   /* Zero count. */
  /* Comparisons with shifting 4-byte boundaries. */
  for (int i = 0; i < 4; i++) {
    char *a = one + i, *b = two + i;
    strncpy(a, "--------11112222", 16);
    strncpy(b, "--------33334444", 16);
    check(memcmp(b, a, 16) > 0);
    check(memcmp(a, b, 16) < 0);
  }
}