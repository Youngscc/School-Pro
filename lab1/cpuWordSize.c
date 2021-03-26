#include <stdio.h>

int Cpu_Word_Size() {
  int x;
  return 8 * sizeof(&x);
}

int main() {
  printf("%d\n", Cpu_Word_Size());
  return 0;
}
