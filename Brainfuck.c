#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const int OPENINGERROR = 1;
const int NUMNEGATIVO = 0;

// TODO fix amount of repetition
// TODO accept user input

void WRITEFILE(FILE *arquivo, char *texto) { fprintf(arquivo, "%s\n", texto); }
/*Testa se o arquivo abriu sem nenhum problema
 * *******************************/
void checkFile(FILE *arquivo, char *mensagem) {
  if (arquivo == NULL) {
    fprintf(stderr, "%s\n", mensagem);
    exit(OPENINGERROR);
  }
}

// Rewritin p2
int sizeofFileArray(FILE *input) {
  int ctr, max, min;
  ctr = max = min = 0;
  char ch = fgetc(input);
  while (!feof(input)) {
    if (ch == '>')
      ctr++;
    else if (ch == '<')
      ctr--;
    if (ctr > max)
      max = ctr;
    else if (ctr < min)
      min = ctr;
    ch = fgetc(input);
  }
  if (min > NUMNEGATIVO)
    return max;
  else
    return max - min;
}

/*Base do arquivo ************************************************************/
void boilerplate(FILE *output) {
  WRITEFILE(output, "#include <stdio.h>");
  WRITEFILE(output, "");
  WRITEFILE(output, "int main (void) {");
  WRITEFILE(output, "int ctr = 0;");
  WRITEFILE(output, "char letra;");
}

void boilerplate2(FILE *output, FILE *input) {
  fprintf(output, "int arr[%d];", sizeofFileArray(input));
  WRITEFILE(output, "");
  WRITEFILE(output, "arr[0] = 0;");
  WRITEFILE(output, "");
}

/*Fim do arquivo *************************************************************/
void boilerplate3(FILE *output) {
  WRITEFILE(output, "");
  WRITEFILE(output, "return 0;");
  WRITEFILE(output, "}");
}

// TODO Arrummar duplicaçao de codigo no arquivo final

void escrevendo(char ch, FILE *output) {
  if (ch == '+') {
    WRITEFILE(output, "arr[ctr]++;");
  } else if (ch == '-') {
    WRITEFILE(output, "arr[ctr]--;");
  } else if (ch == '>') {
    WRITEFILE(output, "ctr++;");
  } else if (ch == '<') {
    WRITEFILE(output, "ctr--;");
  } else if (ch == '[') {
    WRITEFILE(output, "");
    WRITEFILE(output, "while (arr[ctr] != 0) {");
  } else if (ch == ']') {
    WRITEFILE(output, "}");
    WRITEFILE(output, "");
  } else if (ch == '.') {
    WRITEFILE(output, "letra = arr[ctr];");
    WRITEFILE(output, "printf(\"%c\", letra);");
    WRITEFILE(output, "");
    WRITEFILE(output, "letra = 'a' - 'a';");
    WRITEFILE(output, "");
  }
}

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  checkFile(input, "Arquivo nao encontrado");

  FILE *output = fopen("output.c", "w");
  checkFile(output, "Erro ao criar o arquivo");

  boilerplate(output);
  boilerplate2(output, input);

  rewind(input);
  // A maior parte da logica reside neste loop
  char ch = fgetc(input);
  while (!feof(input)) {
    escrevendo(ch, output);
    ch = fgetc(input);
  }

  boilerplate3(output);

  fclose(input);
  fclose(output);

  return 0;
}
