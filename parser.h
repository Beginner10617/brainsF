#ifndef LEXER
#define LEXER
#include "stdio.h"

typedef enum{
  LEFT_SHIFT,
  RIGHT_SHIFT,
  STDIN,
  STDOUT,
  INC,
  DEC,
  OPEN_PAREN,
  CLOSE_PAREN,
  END
} tokenType;

typedef struct{
  size_t index;
  FILE *file;
} lexer;
lexer* createLexer(char* filename);
tokenList* tokenize(lexer* lex);

typedef struct{
  size_t size;
  size_t cap;
  tokenType* list; 
} tokenTypeList;
tokenTypeList* createTokenTypeList();
void append(tokenTypeList* list, tokenType token);

#endif
