#ifndef GENERATION
#define GENERATION
#include "lexer.h"
typedef enum {
  invalidTarget = -1,
  x86_64,
  x86_32,
  arm64,
  arm32
} Target;

typedef struct {
  tokenTypeList* tokens;
  FILE* output;
  Target target;
  int label_count;
  size_t curr_index;
} Generator;

Generator* createGenerator(tokenTypeList* tokens, char* filename, Target target);
void generateCode(Generator* generator);
void freeGenerator(Generator** Generator);
#endif
