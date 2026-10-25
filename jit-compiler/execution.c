#include "execution.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
uint32_t *instruction_array;
size_t instruction_count, instruction_array_capacity;
void init() {
  instruction_array = calloc(1, sizeof(uint32_t));
  instruction_array_capacity = 1;
  instruction_count = 0;
}
void add_instruction(uint32_t instr) {
  if (instruction_count == instruction_array_capacity) {
    size_t new_cap = instruction_array_capacity * 2;
    uint32_t *tmp = realloc(instruction_array, new_cap);
    assert(tmp);
    instruction_array = tmp;
    instruction_array_capacity = new_cap;
  }
  instruction_array[instruction_count++] = instr;
}
void generate_setup_instructions() {
  // setup stack
}
void generate_instruction(tokenWrapper token) {
  switch (token.token) {
  case LEFT_SHIFT:
    break;
  case RIGHT_SHIFT:
    break;
  case STDIN:
    break;
  case STDOUT:
    break;
  case INC:
    break;
  case DEC:
    break;
  case OPEN_PAREN:
    break;
  case CLOSE_PAREN:
    break;
  default:
    break;
  }
}
void execute() {}
