#include <stdio.h>
#include <stdlib.h>

#define OPENINGERROR 1

#define NUMNEGATIVO -1

#define NORMALSTART 0

#define LEFTCELLUSED(CTR) -CTR

#define NONEGATIVECELLS(NUM) NUM

#define FPRINT(STRING, OUTPUT) fprintf(OUTPUT, "%s\n", STRING)

#define HASNEGATIVECELLS(MAX, MIN) MAX + LEFTCELLUSED(MIN)

// GET ON WITH IT!

void checkFile(FILE *arquivo, char *error_message) {
  if (!arquivo) {
    FPRINT(error_message, stderr);
    exit(OPENINGERROR);
  }
}

// Adjusts for progrrams that start to the left instead of right
int ctrPosition(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;

  while (!feof(input)) {
    char ch = fgetc(input);

    switch (ch) {
    case '>':
      ctr++;
      break;
    case '<':
      ctr--;
      break;
    }

    if (ctr >= max)
      max = ctr;
    else
      min = ctr;
  }

  rewind(input);

  if (min > NUMNEGATIVO)
    return NORMALSTART;

  return LEFTCELLUSED(min);
}

int numCellsUsed(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;

  while (!feof(input)) {
    char ch = fgetc(input);

    switch (ch) {
    case '>':
      ctr++;
      break;
    case '<':
      ctr--;
      break;
    }

    if (ctr >= max)
      max = ctr;
    else
      min = ctr;
  }

  rewind(input);

  if (min > NUMNEGATIVO)
    return NONEGATIVECELLS(max);
  else
    return HASNEGATIVECELLS(max, min);
}

void fileBegining(FILE *output) {
  FPRINT("#include <stdio.h>", output);
  FPRINT("", output);
  FPRINT("#define ZERO 'a' - 'a'", output);
  FPRINT("", output);
  FPRINT("int main (void) {", output);
  FPRINT("char letra = ZERO;", output);
}

/*HACK only way to get both these results is with clones of the same function*/
void fileBeginingVariables(FILE *input, FILE *output) {
  fprintf(output, "int arr[%d] = {0};\n", numCellsUsed(input));
  fprintf(output, "int ctr = %d;\n", ctrPosition(input));
  FPRINT("", output);
}

void fileLiteralTranslation(FILE *input, FILE *output) {
  char ch = fgetc(input);

  switch (ch) {
  case '+':
    FPRINT("arr[ctr]++;", output);
    break;
  case '-':
    FPRINT("arr[ctr]--;", output);
    break;
  case '>':
    FPRINT("ctr++;", output);
    break;
  case '<':
    FPRINT("ctr--;", output);
    break;
  case '[':
    FPRINT("", output);
    FPRINT("while (arr[ctr] != 0) {", output);
    break;
  case ']':
    FPRINT("}", output);
    FPRINT("", output);
    break;
  case '.':
    FPRINT("letra = arr[ctr];", output);
    FPRINT("printf(\"%c\", letra);", output);
    FPRINT("", output);
    FPRINT("letra = ZERO;", output);
    FPRINT("", output);
    break;
  // TODO probably doesn't work
  case ',':
    FPRINT("fgets(\"%s\",100,stdin);", output);
    break;
  }
}

void fileEndingFile(FILE *output) {
  FPRINT("", output);
  FPRINT("return 0;", output);
  FPRINT("}", output);
}

int main(int argc, char **argv) {
  FILE *input = fopen(argv[1], "r");
  checkFile(input, "File not found");

  FILE *output = fopen("output.c", "w");
  checkFile(output, "Error generating output file");

  fileBegining(output);
  fileBeginingVariables(input, output);

  while (!feof(input)) {
    fileLiteralTranslation(input, output);
  }

  fileEndingFile(output);

  fclose(input);
  fclose(output);

  return 0;
}
