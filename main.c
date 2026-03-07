#include "stdio.h"
#include "stdlib.h"
#include "generation.h"
#include "string.h"
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

typedef enum {
  targetFlag,
  inputFlag,
  outputFlag
} flag;

int main(int argc, char *argv[]){
  char* ifilename = NULL;
  Target target = invalidTarget;
  char* ofilename = "main.s";
  flag currFlag = inputFlag;
  for(int i=0; i<argc; i++){
    if(!strcmp(argv[i],"-target")){
      currFlag = targetFlag;
      continue;
    } else if (!strcmp(argv[i],"-o")){
      currFlag = outputFlag;
      continue;
    }

    if(currFlag == inputFlag){
      ifilename = argv[i];
    } else if (currFlag == outputFlag) {
      ofilename = argv[i];
    } else if (currFlag == targetFlag) {
      if (!strcmp(argv[i],"x86_64"))
        target = x86_64;
      else if (!strcmp(argv[i],"x86_32"))
        target = x86_32;
      else if (!strcmp(argv[i],"arm64"))
        target = arm64;
      else if (!strcmp(argv[i],"arm32"))
        target = arm32;
      else{
        printf(ERROR 
          "Target not implemented\n"
          COLOR_RESET);
        exit(EXIT_FAILURE);
      }
    }
  }

  if (ifilename == NULL){
    printf(ERROR
    "No input file provided\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  if (target == invalidTarget){
    printf(ERROR
    "Target assembly not provided\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  lexer* lex = createLexer(ifilename);
  tokenTypeList* list = tokenize(lex);
  freeLexer(&lex);
  Generator* gen = createGenerator(list, ofilename, target);
  
  

  return EXIT_SUCCESS;
}
