#include "trap.h"
char one[50];
char two[50];

int main() {
  check(strncpy(one, "abc", 4) == one); /* Returned value. */
  equal(one, "abc");                    /* Did the copy go right? */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 2);
  equal(one, "xycdefgh"); /* Copy cut by count. */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 3); /* Copy cut just before NUL. */
  equal(one, "xyzdefgh");

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 4); /* Copy just includes NUL. */
  equal(one, "xyz");
  equal(one + 4, "efgh"); /* Wrote too much? */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 5); /* Copy includes padding. */
  equal(one, "xyz");
  equal(one + 4, "");
  equal(one + 5, "fgh");

  (void)strcpy(one, "abc");
  (void)strncpy(one, "xyz", 0); /* Zero-length copy. */
  equal(one, "abc");

  (void)strncpy(one, "", 2); /* Zero-length source. */
  equal(one, "");
  equal(one + 1, "");
  equal(one + 2, "c");

  (void)strcpy(one, "hi there");
  (void)strncpy(two, one, 9);
  equal(two, "hi there"); /* Just paranoia. */
  equal(one, "hi there"); /* Stomped on source? */
}