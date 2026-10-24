#ifndef LEXER
#define LEXER
#include "stdio.h"

typedef enum {
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

typedef struct {
  size_t index;
  FILE *file;
  char *filename;
} lexer;
lexer *createLexer(char *filename);
tokenTypeList *tokenize(lexer *lex);
void freeLexer(lexer **lexer);

typedef struct {
  tokenType token;
  int occ; // occurence
} tokenWrapper;

struct tokenTypeList {
  size_t size;
  size_t cap;
  tokenWrapper *list;
};
tokenTypeList *createTokenTypeList();
void append(tokenTypeList *list, tokenType token);
void freeTokenTypeList(tokenTypeList **list);
tokenWrapper tokenAt(tokenTypeList *list, size_t index);

// For error messages
typedef struct {
  int *values;
  size_t size, cap;
} stack;
void pushstk(stack *stk, int line, int col);
int *popstk(stack *stk);
stack *createEmptyStack();
#endif
