#include "generation.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define GREEN "\033[32m"
#define COLOR_RESET "\x1b[0m"

typedef enum { targetFlag, inputFlag, outputFlag } flag;

int main(int argc, char *argv[]) {
  char *ifilename = NULL;
  Target target = invalidTarget;
  char *ofilename = "main.s";
  flag currFlag = inputFlag;
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "-target")) {
      currFlag = targetFlag;
      continue;
    } else if (!strcmp(argv[i], "-o")) {
      currFlag = outputFlag;
      continue;
    } else if (!strcmp(argv[i], "--version")) {
      printf(GREEN "BRAINFUCK COMPILER VERSION 1.0\n" COLOR_RESET);
      return 0;
    }

    if (currFlag == inputFlag) {
      ifilename = argv[i];
    } else if (currFlag == outputFlag) {
      ofilename = argv[i];
    } else if (currFlag == targetFlag) {
      if (!strcmp(argv[i], "x86_64"))
        target = x86_64;
      else if (!strcmp(argv[i], "x86_32"))
        target = x86_32;
      else if (!strcmp(argv[i], "arm64-mac"))
        target = arm64_mac;
      else if (!strcmp(argv[i], "arm64-linux"))
        target = arm64_linux;
      else if (!strcmp(argv[i], "arm32"))
        target = arm32;
      else {
        printf(ERROR "Target not implemented\n" COLOR_RESET);
        exit(EXIT_FAILURE);
      }
    }
  }

  if (ifilename == NULL) {
    printf(ERROR "No input file provided\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  if (target == invalidTarget) {
    printf(ERROR "Target assembly not provided\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  lexer *lex = createLexer(ifilename);
  tokenTypeList *list = tokenize(lex);
  freeLexer(&lex);
  Generator *gen = createGenerator(list, ofilename, target);
  generateCode(gen);
  freeGenerator(&gen);
  return EXIT_SUCCESS;
}
