#include "generation.h"
#include "stdlib.h"
#include "assert.h"
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"
// helper struct/functions
typedef struct{
  int* val;
  int sz, cap;
} intStack;
intStack* createIntStack(){
  intStack* stk = malloc(sizeof(intStack));
  if(stk == NULL){
    printf(ERROR
    "Unable to create stack\n"
           COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  stk->cap = 2;
  stk->sz  = 0;
  stk->val = malloc(sizeof(int) * stk->cap);
  if(stk->val == NULL){
    printf(ERROR
    "Unable to allocate memory for stack\n"
           COLOR_RESET);
  }
  return stk;
}

int top(intStack* stk){
  assert(stk->sz > 0);
  return stk->val[stk->sz - 1];
}

int pop(intStack* stk){
  stk->sz--;
  return stk->val[stk->sz];
}
void push(intStack* stk, int v){
  if(stk->sz >= stk->cap){
    while(stk->sz >= stk->cap)
      stk->cap *= 2;
    stk->val = realloc(stk->val, 
    sizeof(int) * stk->cap);
    if(stk->val==NULL){
      printf(ERROR
      "Unable to reallocate memory for stack push\n"
             COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  stk->val[stk->sz] = v;
  stk->sz++;
}

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

void generateCode(Generator* gen){
  size_t sz = gen->tokens->size;
  tokenType curr_token;


//
  if(gen->target == x86_64)
  {
    fprintf(gen->output,
    "global _start\n_start:\n"
    "    sub rsp, 32768\n"
    "    mov rbx, rsp\n");
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
  
  int label_count = 0;
  intStack* stk = createIntStack();
  
  while (gen->curr_index < sz){
    curr_token = tokenAt(gen->tokens,
                  gen->curr_index);
    
    // generate assembly

    if(gen->target == x86_64)
    {
      //assert("Target not implemented" && NULL);
      switch (curr_token) {
        case LEFT_SHIFT:
          fprintf(gen->output,
          "    sub rbx, 1\n");
          break;
        case RIGHT_SHIFT:
          fprintf(gen->output,
          "    add rbx, 1\n");
          break;
        case STDIN:// linux is assumed
          fprintf(gen->output,
          "    mov rax, 1\n" 
          "    mov rdi, 0\n"
          "    mov rsi, rbx\n"
          "    mov rdx, 1\n"
          "    syscall\n"
          );
          break;
        case STDOUT:// linux is assumed
           fprintf(gen->output,
          "    mov rax, 1\n" 
          "    mov rdi, 1\n"
          "    mov rsi, rbx\n"
          "    mov rdx, 1\n"
          "    syscall\n"
          );
          break;
        case INC:
          fprintf(gen->output,
          "    add byte [rbx], 1\n");
          break;
        case DEC:
          fprintf(gen->output,
          "    sub byte [rbx], 1\n");
          break;
        case OPEN_PAREN:
          fprintf(gen->output,
          "    mov al, [rbx]\n"
          "    cmp al, 0\n"
          "    je LABEL1%d\n"
          "LABEL0%d:\n",
          label_count, label_count);
          push(stk, label_count);
          label_count++;
          break;
        case CLOSE_PAREN:{
          int idx = pop(stk);
          fprintf(gen->output,
          "    mov al, [rbx]\n"
          "    cmp al, 0\n"
          "    jne LABEL0%d\n"
          "LABEL1%d:\n",
          idx, idx);
          break;
        }
        default:
          assert("Something went wrong" && NULL);
      }

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

  // generate exit code 
  if (gen->target == x86_64){
    fprintf(gen->output,
    "    mov rax, 60\n"
    "    mov rdi, 0\n"
    "    syscall");
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
  gen->curr_index = 0;
}
