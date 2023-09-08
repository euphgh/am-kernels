#include "trap.h"
#include <stdint.h>
#include <string.h>
#define N 32
uint8_t src[N];
uint8_t dst[N];

void reset(uint8_t arr[], uint8_t base) {
  int i;
  for (i = 0; i < N; i++) {
    arr[i] = i + base;
  }
}
// 检查[l,r)区间中的值是否依次为val, val + 1, val + 2...
void check_seq(uint8_t arr[], int l, int r, uint8_t base) {
  int i;
  for (i = l; i < r; i++) {
    assert(arr[i] == base + i - l);
  }
}

// 检查[l,r)区间中的值是否均为val
void check_eq(uint8_t arr[], int l, int r, uint8_t val) {
  int i;
  for (i = l; i < r; i++) {
    assert(arr[i] == val);
  }
}

int main() {
  int l, r;
  for (l = 0; l < N; l++) {
    for (r = l + 1; r <= N; r++) {
      reset(src, 0);
      reset(dst, 32);
      memcpy(dst + l, src + l, r - l);
      check_seq(dst, 0, l, 32);
      check_seq(dst, l, r, 0 + l);
      check_seq(dst, r, N, 32 + r);
    }
  }
}