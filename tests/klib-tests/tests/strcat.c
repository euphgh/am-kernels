#include "trap.h"
char one[50];
char two[50];
int main() {
  (void)strcpy(one, "ijk");
  check(strcat(one, "lmn") == one); /* Returned value. */
  equal(one, "ijklmn");             /* Basic test. */

  (void)strcpy(one, "x");
  (void)strcat(one, "yz");
  equal(one, "xyz");    /* Writeover. */
  equal(one + 4, "mn"); /* Wrote too much? */

  (void)strcpy(one, "gh");
  (void)strcpy(two, "ef");
  (void)strcat(one, two);
  equal(one, "ghef"); /* Basic test encore. */
  equal(two, "ef");   /* Stomped on source? */

  (void)strcpy(one, "");
  (void)strcat(one, "");
  equal(one, ""); /* Boundary conditions. */
  (void)strcpy(one, "ab");
  (void)strcat(one, "");
  equal(one, "ab");
  (void)strcpy(one, "");
  (void)strcat(one, "cd");
  equal(one, "cd");
}