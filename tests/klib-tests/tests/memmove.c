#include "trap.h"

char one[50];
char two[50];

int main() {
  check(memmove(one, "abc", 4) == one); /* Returned value. */
  equal(one, "abc");                    /* Did the copy go right? */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, "xyz", 2);
  equal(one, "axydefgh"); /* Basic test. */

  (void)strcpy(one, "abc");
  (void)memmove(one, "xyz", 0);
  equal(one, "abc"); /* Zero-length copy. */

  (void)strcpy(one, "hi there");
  (void)strcpy(two, "foo");
  (void)memmove(two, one, 9);
  equal(two, "hi there"); /* Just paranoia. */
  equal(one, "hi there"); /* Stomped on source? */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, one, 9);
  equal(one, "aabcdefgh"); /* Overlap, right-to-left. */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, one + 2, 7);
  equal(one, "acdefgh"); /* Overlap, left-to-right. */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one, one, 9);
  equal(one, "abcdefgh"); /* 100% overlap. */
}
