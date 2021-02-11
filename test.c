#include <stdio.h>
#include <threads.h>

int main(int arc, char* argv[]) {

  printf("can we int a mut?\n");

  mtx_t mut;
  if (0 != mtx_init(&mut, mtx_plain)) {
    printf("nope.\n");
    return -1;
  }

  printf("created: %p\n", &mut);

  return 0;
}
