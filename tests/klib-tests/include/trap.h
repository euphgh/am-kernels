#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib-macros.h>
#include <klib.h>

__attribute__((noinline)) void check(bool cond) {
  if (!cond)
    halt(1);
}

#define STREQ(a, b) (strcmp((a), (b)) == 0)
/* Complain if first two args don't strcmp as equal.  */
void equal(const char *a, const char *b) {
  check(a != NULL && b != NULL && STREQ(a, b));
}
#endif
