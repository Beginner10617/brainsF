#include "lexer.h"
#include "stdlib.h"
#include "assert.h"
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

// helper function
void push_char(char* str, char c, size_t sz){
  assert(sz > 0 && str);
  char tmp0 = c; size_t i = sz - 1;
  char tmp1;
  while(1){
    tmp1 = str[i];
    str[i] = tmp0;
    tmp0 = tmp1;
    if(i == 0) break;
    i--;
  }
}


lexer* createLexer(char* filename){
  lexer* output = malloc(sizeof(lexer));
  if(output == NULL){
    printf(ERROR 
    "Unable to allocate memory for lexer of %s\n"
    COLOR_RESET, filename);
    exit(EXIT_FAILURE);
  }
  output->file = fopen(filename, "r");
  if(output->file == NULL){
    printf(ERROR "Unable to read %s\n"
    COLOR_RESET, filename);
    exit(EXIT_FAILURE);
  }
  output->index = 0;
  return output;
}

tokenTypeList* tokenize(lexer* lex){
  if (lex == NULL){
    printf(ERROR
    "NULL Lexer Pointer passed to tokenize\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  char c; int nesting = 0;
  tokenTypeList* output = createTokenTypeList();
  char buf[12]; buf[11] = '\0';
  while ( (c = fgetc(lex->file)) != EOF){
    tokenType token;
    push_char(buf, c, 11);
    switch (c) {
      case '<':
        token = LEFT_SHIFT;
        break;
      case '>':
        token = RIGHT_SHIFT;
        break;
      case ',':
        token = STDIN;
        break;
      case '.':
        token = STDOUT;
        break;
      case '+':
        token = INC;
        break;
      case '-':
        token = DEC;
        break;
      case '[':
        nesting++;
        token = OPEN_PAREN;
        break;
      case ']':
        nesting--;
        token = CLOSE_PAREN;
        break;
      default:
        token = NONE;
    }
    if(token == NONE) continue;
    append(output, token);
  }
  if(nesting){
    printf("%s\n",buf);
    printf(ERROR 
    "         ^ Expected a ']' here\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  return output;
}

void freeLexer(lexer** lexer){
  if(lexer && *lexer){
    if ((*lexer)->file)
      fclose( (*lexer)->file);
    free(*lexer);
    *lexer = NULL;
    return;
  }
  printf(WARNING
  "Trying to free NULL pointer\n"
  COLOR_RESET);
}

tokenTypeList* createTokenTypeList(){
  tokenTypeList* output = malloc(
    sizeof(tokenTypeList)
  );
  if(output == NULL){
    printf(ERROR 
    "Unable to allocate memory for list\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  output->size = 1;
  output->cap = 2;
  output->list = malloc(
    sizeof(tokenType) * output->cap
  );
  if(output->list == NULL){
    printf(ERROR
    "Unable to allocate memory for output->list\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  return output;
}

void append(tokenTypeList* list, tokenType token){
  if(list == NULL){
    printf(ERROR
    "NULL Pointer passed to append\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  if(list->size >= list->cap){
    while(list->size >= list->cap)
      list->cap *= 2;
    list->list = realloc(list->list, 
    sizeof(tokenType) * list->cap);
    if(list->list == NULL){
      printf(ERROR
      "Unable to reallocate memory to list\n"
      COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  list->list[list->size] = token;
  list->size++;
}

void freeTokenTypeList(tokenTypeList** list)
{
  if(list && *list){
    free( (*list)->list );
    free( *list );
    *list = NULL;
    return;
  }
  printf(WARNING
  "Trying to free NULL pointer\n"
  COLOR_RESET);
}

tokenType tokenAt(tokenTypeList* list, size_t index){
  if (index >= list->size){
    printf(ERROR
    "Trying to access index %zu on a list of size %zu\n"
    COLOR_RESET, index, list->size);
    exit(EXIT_FAILURE);
  }
  return list->list[index];
}
