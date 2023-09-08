#include "trap.h"

char one[50];
char two[50];
#define SIMPLE_COPY(fn, n, str)                                                \
  do {                                                                         \
    int __n;                                                                   \
    char *cp;                                                                  \
    for (__n = 0; __n < (int)sizeof(one); ++__n)                               \
      one[__n] = 'Z';                                                          \
    fn(one, str);                                                              \
    for (cp = one, __n = 0; __n < n; ++__n, ++cp)                              \
      check(*cp == '0' + (n % 10));                                            \
    check(*cp == '\0');                                                        \
  } while (0)

int main() {
  int i;
  check(strcpy(one, "abcd") == one); /* Returned value. */
  equal(one, "abcd");                /* Basic test. */

  (void)strcpy(one, "x");
  equal(one, "x");      /* Writeover. */
  equal(one + 2, "cd"); /* Wrote too much? */

  (void)strcpy(two, "hi there");
  (void)strcpy(one, two);
  equal(one, "hi there"); /* Basic test encore. */
  equal(two, "hi there"); /* Stomped on source? */

  (void)strcpy(one, "");
  equal(one, ""); /* Boundary condition. */

  for (i = 0; i < 16; i++) {
    (void)strcpy(one + i, "hi there"); /* Unaligned destination. */
    equal(one + i, "hi there");
    (void)strcpy(two, one + i); /* Unaligned source. */
    equal(two, "hi there");
  }

  SIMPLE_COPY(strcpy, 0, "");
  SIMPLE_COPY(strcpy, 1, "1");
  SIMPLE_COPY(strcpy, 2, "22");
  SIMPLE_COPY(strcpy, 3, "333");
  SIMPLE_COPY(strcpy, 4, "4444");
  SIMPLE_COPY(strcpy, 5, "55555");
  SIMPLE_COPY(strcpy, 6, "666666");
  SIMPLE_COPY(strcpy, 7, "7777777");
  SIMPLE_COPY(strcpy, 8, "88888888");
  SIMPLE_COPY(strcpy, 9, "999999999");
  SIMPLE_COPY(strcpy, 10, "0000000000");
  SIMPLE_COPY(strcpy, 11, "11111111111");
  SIMPLE_COPY(strcpy, 12, "222222222222");
  SIMPLE_COPY(strcpy, 13, "3333333333333");
  SIMPLE_COPY(strcpy, 14, "44444444444444");
  SIMPLE_COPY(strcpy, 15, "555555555555555");
  SIMPLE_COPY(strcpy, 16, "6666666666666666");

  /* Simple test using implicitly coerced `void *' arguments.  */
  const void *src = "frobozz";
  void *dst = one;
  check(strcpy(dst, src) == dst);
  equal(dst, "frobozz");
}