#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define OPENINGERROR 1

#define NUMNEGATIVO -1

#define NORMALSTART 0

#define LEFTSTART(CTR) -CTR

#define LOOP(END) for (int i = 0; i < END; i++)

#define PRINT(STRING) printf("%s\n", STRING);

#define FPRINT(STRING, OUTPUT) fprintf(OUTPUT, "%s\n", STRING)

// GET ON WITH IT!

void checkFile(FILE *arquivo, char *error_message) {
  if (!arquivo) {
    FPRINT(error_message, stderr);
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
}

void fileLiteralTranslation(FILE *output, char ch) {
  if (ch == '+') {
    FPRINT("arr[ctr]++;", output);
  } else if (ch == '-') {
    FPRINT("arr[ctr]--;", output);
  } else if (ch == '>') {
    FPRINT("ctr++;", output);
  } else if (ch == '<') {
    FPRINT("ctr--;", output);
  } else if (ch == '[') {
    FPRINT("", output);
    FPRINT("while (arr[ctr] != 0) {", output);
  } else if (ch == ']') {
    FPRINT("}", output);
    FPRINT("", output);
  } else if (ch == '.') {
    FPRINT("letra = arr[ctr];", output);
    FPRINT("printf(\"%c\", letra);", output);
    FPRINT("", output);
    FPRINT("letra = ZERO;", output);
    FPRINT("", output);
    // TODO probably doesn't work
  } else if (ch == ',') {
    FPRINT("fgets(\"%s\",50,stdin);", output);
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

  char ch = fgetc(input);
  while (!feof(input)) {
    fileLiteralTranslation(output, ch);
    ch = fgetc(input);
  }

  fileEndingFile(output);

  fclose(input);
  fclose(output);

  return 0;
}
