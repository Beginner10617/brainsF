#include "lexer.h"
#include "assert.h"
#include "stdlib.h"
#include <stdlib.h>
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

// helper function
void push_char(char *str, char c, size_t sz) {
  assert(sz > 0 && str);
  char tmp0 = c;
  size_t i = sz - 1;
  char tmp1;
  while (1) {
    tmp1 = str[i];
    str[i] = tmp0;
    tmp0 = tmp1;
    if (i == 0)
      break;
    i--;
  }
}

lexer *createLexer(char *filename) {
  lexer *output = malloc(sizeof(lexer));
  if (output == NULL) {
    printf(ERROR "Unable to allocate memory for lexer of %s\n" COLOR_RESET,
           filename);
    exit(EXIT_FAILURE);
  }
  output->file = fopen(filename, "r");
  if (output->file == NULL) {
    printf(ERROR "Unable to read %s\n" COLOR_RESET, filename);
    exit(EXIT_FAILURE);
  }
  output->filename = filename;
  output->index = 0;
  return output;
}

tokenTypeList *tokenize(lexer *lex) {
  if (lex == NULL) {
    printf(ERROR "NULL Lexer Pointer passed to tokenize\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  char c;
  int nesting = 0, line = 1, pos = 1;
  tokenTypeList *output = createTokenTypeList();
  stack *errorMessageStack = createEmptyStack();
  char buf[12];
  buf[11] = '\0';
  while ((c = fgetc(lex->file)) != EOF) {
    tokenType token;
    push_char(buf, c, 11);
    switch (c) {
    case '<':
      token = LEFT_SHIFT;
      pos++;
      break;
    case '>':
      token = RIGHT_SHIFT;
      pos++;
      break;
    case ',':
      token = STDIN;
      pos++;
      break;
    case '.':
      token = STDOUT;
      pos++;
      break;
    case '+':
      token = INC;
      pos++;
      break;
    case '-':
      token = DEC;
      pos++;
      break;
    case '[':
      nesting++;
      pos++;
      token = OPEN_PAREN;
      // For error message
      if (nesting > 0) {
        pushstk(errorMessageStack, line, pos);
      }
      break;
    case ']':
      nesting--;
      pos++;
      token = CLOSE_PAREN;
      if (nesting > 0) {
        popstk(errorMessageStack);
        popstk(errorMessageStack);
      }
      break;
    case '\n':
      line++;
      pos = 1;
      token = NONE;
      break;
    default:
      pos++;
      token = NONE;
    }
    if (token == NONE)
      continue;
    append(output, token);
    if (nesting < 0) {
      printf("%s:%d:%d: %s\n", lex->filename, line, pos, buf);
      printf(ERROR "Expected a '[' here\n" COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  if (nesting) {
    line = *popstk(errorMessageStack);
    pos = *popstk(errorMessageStack);
    printf("%s:%d:%d: %s\n", lex->filename, line, pos, buf);
    printf(ERROR "Expected a ']' corresponding to this\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  return output;
}

void freeLexer(lexer **lexer) {
  if (lexer && *lexer) {
    if ((*lexer)->file)
      fclose((*lexer)->file);
    free(*lexer);
    *lexer = NULL;
    return;
  }
  printf(WARNING "Trying to free NULL pointer\n" COLOR_RESET);
}

tokenTypeList *createTokenTypeList() {
  tokenTypeList *output = malloc(sizeof(tokenTypeList));
  if (output == NULL) {
    printf(ERROR "Unable to allocate memory for list\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  output->size = 0;
  output->cap = 2;
  output->list = malloc(sizeof(tokenType) * output->cap);
  if (output->list == NULL) {
    printf(ERROR "Unable to allocate memory for output->list\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  return output;
}

void append(tokenTypeList *list, tokenType token) {
  if (list == NULL) {
    printf(ERROR "NULL Pointer passed to append\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  tokenType lastToken = NONE;
  if (list->size > 0)
    lastToken = list->list[list->size - 1].token;
  if (lastToken != NONE) {
    if (lastToken == token && lastToken != OPEN_PAREN &&
        lastToken != CLOSE_PAREN) {
      list->list[list->size - 1].occ++;
      return;
    }
    if ((lastToken == LEFT_SHIFT && token == RIGHT_SHIFT) ||
        (lastToken == RIGHT_SHIFT && token == LEFT_SHIFT) ||
        (lastToken == INC && token == DEC) ||
        (lastToken == DEC && token == INC)) {
      list->list[list->size - 1].occ--;
      if (list->list[list->size - 1].occ < 0) {
        list->list[list->size - 1].token = token;
        list->list[list->size - 1].occ *= -1;
      }
      return;
    }
  }
  if (list->size >= list->cap) {
    while (list->size >= list->cap)
      list->cap *= 2;
    list->list = realloc(list->list, sizeof(tokenWrapper) * list->cap);
    if (list->list == NULL) {
      printf(ERROR "Unable to reallocate memory to list\n" COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  tokenWrapper tokenW;
  tokenW.token = token;
  tokenW.occ = 1;
  list->list[list->size] = tokenW;
  list->size++;
}

void freeTokenTypeList(tokenTypeList **list) {
  if (list && *list) {
    free((*list)->list);
    free(*list);
    *list = NULL;
    return;
  }
  printf(WARNING "Trying to free NULL pointer\n" COLOR_RESET);
}

tokenWrapper tokenAt(tokenTypeList *list, size_t index) {
  if (index >= list->size) {
    printf(ERROR
           "Trying to access index %zu on a list of size %zu\n" COLOR_RESET,
           index, list->size);
    exit(EXIT_FAILURE);
  }
  return list->list[index];
}

stack *createEmptyStack() {
  stack *stk = malloc(sizeof(stack));
  if (stk == NULL) {
    printf(ERROR
           "Unable to allocate space for error message stack\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  stk->size = 0;
  stk->cap = 1;
  stk->values = malloc(sizeof(int) * stk->cap);
  if (stk->values == NULL) {
    printf(ERROR "Unable to create Empty Stack\n" COLOR_RESET);
  }
  return stk;
}

void pushstk(stack *stk, int line, int col) {
  if (stk == NULL) {
    printf(WARNING "PASSED NULL POINTER OF STACK TO PUSH\n" COLOR_RESET);
    return;
  }
  if (stk->size + 2 > stk->cap) {
    while (stk->size + 2 > stk->cap)
      stk->cap *= 2;
    stk->values = realloc(stk->values, stk->cap);
    if (stk->values == NULL) {
      printf(ERROR "Unable to realloc space to stack values\n" COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  stk->values[stk->size] = line;
  stk->size++;
  stk->values[stk->size] = col;
  stk->size++;
}
int *popstk(stack *stk) {
  if (stk->size < 2)
    return NULL;
  int *out = stk->values + (stk->size - 2);
  stk->size -= 2;
  return out;
}
