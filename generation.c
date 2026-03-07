#include "generation.h"
#include "stdlib.h"
#include "assert.h"
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

Generator* createGenerator(tokenTypeList* tokens, char* filename, Target target){
  if(tokens == NULL){
    printf(ERROR 
    "NULL Pointer for tokens passed to generator\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  Generator* generator = malloc(sizeof(Generator));
  if (generator == NULL){
    printf(ERROR
    "Unable to allocate memory for generator\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  generator->tokens = tokens;
  generator->label_count = 0;
  generator->curr_index = 0;
  generator->output = fopen(filename, "w");
  if(generator->output == NULL){
    printf(ERROR
    "Unable to create %s\n"
    COLOR_RESET, filename);
  }
  generator->target = target;
  return generator;
}

void freeGenerator(Generator** generator){
  if(generator && *generator){
    freeTokenTypeList( &(*generator)->tokens );
    fclose((*generator)->output);
    free(*generator);
    *generator = NULL;
    return;
  }
  printf(WARNING
  "Trying to free NULL pointer\n"
  COLOR_RESET);
}

void generateCode(Generator* gen){
  size_t sz = gen->tokens->size;
  tokenType curr_token;
  while (gen->curr_index < sz){
    curr_token = tokenAt(gen->tokens,
                  gen->curr_index);
    
    // generate assembly

    if(gen->target == x86_64)
    {
      //assert("Target not implemented" && NULL);
      

    }
    else if(gen->target == x86_32)
    {
      assert("Target not implemented" && NULL);
    }
    else if(gen->target == arm64)
    {
      assert("Target not implemented" && NULL);
    }
    else if(gen->target == arm32)
    {
      assert("Target not implemented" && NULL);
    }


    gen->curr_index++;
  }
  gen->curr_index = 0;
  gen->label_count = 0;
}
