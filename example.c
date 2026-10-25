#include <libkern/OSCacheControl.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
  // ARM64 machine code:
  // mov w0, #42
  // ret
  const uint32_t instructions[] = {0x52800540, 0xD65F03C0};

  size_t code_size = sizeof(instructions);

  void *mem =
      mmap(NULL, (size_t)getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC,
           MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);

  if (mem == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  // Switch the JIT region into write mode.
  pthread_jit_write_protect_np(0);

  memcpy(mem, instructions, code_size);

  // Switch back to execute mode.
  pthread_jit_write_protect_np(1);

  // Ensure the CPU sees the newly written instructions.
  sys_icache_invalidate(mem, code_size);

  // Treat the generated code as a function returning int.
  int (*generated_function)(void) = (int (*)(void))mem;

  int result = generated_function();

  printf("Result: %d\n", result);

  munmap(mem, (size_t)getpagesize());
  return 0;
}
