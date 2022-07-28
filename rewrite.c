#include <stdio.h>
#include <stdlib.h>

#define OPENINGERROR 1

#define NUMNEGATIVO -1

#define NORMALSTART 0

#define LEFTSTART(CTR) -CTR;

#define LOOP(END) for (int i = 0; i < END; i++)

#define FLOOP(INPUT)                                                           \
  for (char ch = fgetc(INPUT); !feof(INPUT); ch = fgetc(INPUT))

#define PRINT(STRING) printf("%s\n", STRING);

#define FPRINT(STRING, OUTPUT) fprintf(OUTPUT, "%s\n", STRING);

// GET ON WITH IT!

void checkFile(FILE *arquivo, char *error_message) {
  if (!arquivo) {
    FPRINT(error_message, stderr);
    exit(OPENINGERROR);
  }
}

int sizeoffile(FILE *input) {
  int num = 0;
  FLOOP(input) { num++; }

  rewind(input);

  return num;
}

/*HACK only way to get both these results is with clones of the same function */
int ctrPosition(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;

  FLOOP(input) {
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

  FLOOP(input) {
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

int main(void) { return 0; }
