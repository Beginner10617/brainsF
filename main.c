#include "stdio.h"
#include "stdlib.h"
#include "lexer.h"
int main(int argc, char *argv[]){
  lexer* lex = createLexer("HelloWorld.bf");
  tokenTypeList* list = tokenize(lex);
  printf("size=%zu\tcap=%zu\n",
         list->size,
         list->cap);
  freeLexer(&lex);
  if(lex == NULL){
    printf("freeLexer working!\n");
  }
  return EXIT_SUCCESS;
}
