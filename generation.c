#include "generation.h"
#include "stdlib.h"
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
