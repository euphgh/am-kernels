#include <limits.h>
#include <stdio.h>
#define TEST_DATA                                                              \
  0, INT_MAX / 17, INT_MAX, INT_MIN, INT_MIN + 1, UINT_MAX / 17, INT_MAX / 17, \
      UINT_MAX

#define MAC_STR(x) #x
#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

int data[] = {TEST_DATA};

const char *testMain = "\
#include \"trap.h\"\n\
int main() {\
  int data[] = {%s};\
  const char* ref[] = {%s};\
  char ans[32];\
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {\
    sprintf(ans, \"%%d\", data[i]);\
    check(strcmp(ans, ref[i]) == 0);\
  }\
  return 0;\
}\
";
int main(int argc, char *argv[]) {
  char dataStr[1024];
  char *dataPtr = dataStr;
  char refStr[1024];
  char *refPtr = refStr;
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
    refPtr += sprintf(refPtr, "\"%d\", ", data[i]);
    dataPtr += sprintf(dataPtr, "%d, ", data[i]);
  }
  printf(testMain, dataStr, refStr);
  return 0;
}