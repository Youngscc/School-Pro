#include <stdio.h>

int is_little_endian() {
  unsigned short x, *p;
  x = 0;
  p = &x;
  *(char*) p = 0x22;
  return x == 0x22;
}

int main() {
  puts(is_little_endian() ? "Little Endian" : "Big Endian");
  return 0;
}
