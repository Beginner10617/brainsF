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
  NONE
} tokenType;

typedef struct tokenTypeList tokenTypeList;

typedef struct{
  size_t index;
  FILE *file;
} lexer;
lexer* createLexer(char* filename);
tokenTypeList* tokenize(lexer* lex);
void freeLexer(lexer** lexer);

struct tokenTypeList{
  size_t size;
  size_t cap;
  tokenType* list; 
};
tokenTypeList* createTokenTypeList();
void append(tokenTypeList* list, tokenType token);

#endif
