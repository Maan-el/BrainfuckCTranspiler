#include <stdio.h>
#include <stdlib.h>

#define OPENINGERROR 1

#define NUMNEGATIVO -1

#define NORMALSTART 0

#define LEFTSTART(CTR) -CTR

// GET ON WITH IT!

void printtofile(char *frase, FILE *output) { fprintf(output, "%s\n", frase); }

void checkFile(FILE *arquivo, char *error_message) {
  if (!arquivo) {
    printtofile(error_message, stderr);
    exit(OPENINGERROR);
  }
}

int ctrPosition(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;

  while (!feof(input)) {
    char ch = fgetc(input);
    if (ch == '>')
      ctr++;
    else if (ch == '<')
      ctr--;
    if (ctr > max)
      max = ctr;
    else if (ctr < min)
      min = ctr;
  }

  rewind(input);

  if (min > NUMNEGATIVO)
    return NORMALSTART;

  return LEFTSTART(min);
}

int numCellsUsed(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;

  while (!feof(input)) {
    char ch = fgetc(input);
    if (ch == '>')
      ctr++;
    else if (ch == '<')
      ctr--;
    if (ctr > max)
      max = ctr;
    else if (ctr < min)
      min = ctr;
  }

  rewind(input);

  if (min > NUMNEGATIVO)
    return max;
  else
    return max - min;
}

void fileBegining(FILE *output) {
  printtofile("#include <stdio.h>", output);
  printtofile("", output);
  printtofile("#define ZERO 'a' - 'a'", output);
  printtofile("", output);
  printtofile("int main (void) {", output);
  printtofile("char letra = ZERO;", output);
}

/*HACK only way to get both these results is with clones of the same function*/
void fileBeginingVariables(FILE *input, FILE *output) {
  fprintf(output, "int arr[%d];\n", numCellsUsed(input));
  fprintf(output, "int ctr = %d;\n", ctrPosition(input));
}

void fileLiteralTranslation(FILE *output, char ch) {
  if (ch == '+') {
    printtofile("arr[ctr]++;", output);
  } else if (ch == '-') {
    printtofile("arr[ctr]--;", output);
  } else if (ch == '>') {
    printtofile("ctr++;", output);
  } else if (ch == '<') {
    printtofile("ctr--;", output);
  } else if (ch == '[') {
    printtofile("", output);
    printtofile("while (arr[ctr] != 0) {", output);
  } else if (ch == ']') {
    printtofile("}", output);
    printtofile("", output);
  } else if (ch == '.') {
    printtofile("letra = arr[ctr];", output);
    printtofile("printf(\"%c\", letra);", output);
    printtofile("", output);
    printtofile("letra = ZERO;", output);
    printtofile("", output);
    // TODO probably doesn't work
  } else if (ch == ',') {
    printtofile("fgets(\"%s\",50,stdin);", output);
  }
}

void fileEndingFile(FILE *output) {
  printtofile("", output);
  printtofile("return 0;", output);
  printtofile("}", output);
}

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  checkFile(input, "File not found");

  FILE *output = fopen("output.c", "w");
  checkFile(output, "Error generating output file");

  fileBegining(output);
  fileBeginingVariables(input, output);

  char ch = fgetc(input);
  while (!feof(input)) {
    fileLiteralTranslation(output, ch);
    ch = fgetc(input);
  }

  // Just in case
  rewind(input);

  fileEndingFile(output);

  fclose(input);
  fclose(output);

  return 0;
}
