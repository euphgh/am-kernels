#include "trap.h"

int main() {
  check(strlen("") == 0);     /* Empty. */
  check(strlen("a") == 1);    /* Single char. */
  check(strlen("abcd") == 4); /* Multiple chars. */
  {
    char buf[4096];
    int i;
    char *p;
    for (i = 0; i < 0x100; i++) {
      p = (char *)((unsigned long int)(buf + 0xff) & ~0xff) + i;
      strcpy(p, "OK");
      strcpy(p + 3, "BAD/WRONG");
      check(strlen(p) == 2);
    }
  }
}