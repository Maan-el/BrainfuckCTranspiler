#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int OPENINGERROR = 1;
const int NUMNEGATIVO = 0;

#define FLOOP(input)                                                           \
  for (char ch = fgetc(input); !feof(input); ch = fgetc(input))
#define WRITEFILE(arquivo, texto) fprintf(arquivo, "%s\n", texto)

/*Testa se o arquivo abriu sem nenhum problema *******************************/
void checkFile(FILE *arquivo, char *mensagem) {
  if (arquivo == NULL) {
    fprintf(stderr, "%s\n", mensagem);
    exit(OPENINGERROR);
  }
}

/*Nao esta sendo usado ainda *************************************************/
/*
int sizeofFile(FILE *arquivo) {
  int size, safesize;

  while (!feof(arquivo)) {
    size++;
  }
  // Tamanho incluindo o \n e o \0
  safesize = size + 2;
  return safesize;
}

*/

// Rewritin p2
int size(FILE *input) {
  int ctr, max, min;
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
  if (min > NUMNEGATIVO)
    return max;
  else
    return max - min;
}

/*Base do arquivo ************************************************************/
void boilerplate(FILE *arq_out) {
  WRITEFILE(arq_out, "#include <stdio.h>");
  WRITEFILE(arq_out, "");
  WRITEFILE(arq_out, "int main (void) {");
  WRITEFILE(arq_out, "int arr[30000];");
  WRITEFILE(arq_out, "arr[0] = 0;");
  // fprintf(arq_out, "int arr[%d];\n", sizeofFileArray(arq_out));
  WRITEFILE(arq_out, "int ctr = 0;");
  WRITEFILE(arq_out, "char letra;");
  WRITEFILE(arq_out, "");
}

/*Fim do arquivo *************************************************************/
void boilerplate2(FILE *arq_out) {
  WRITEFILE(arq_out, "");
  WRITEFILE(arq_out, "return 0;");
  WRITEFILE(arq_out, "}");
}

// TODO Arrummar duplicaçao de codigo no arquivo final

void escrevendo(char ch, FILE *arq_out) {
  if (ch == '+') {
    WRITEFILE(arq_out, "arr[ctr]++;");
  } else if (ch == '>') {
    WRITEFILE(arq_out, "ctr++;");
  } else if (ch == '<') {
    WRITEFILE(arq_out, "ctr--;");
  } else if (ch == '-') {
    WRITEFILE(arq_out, "arr[ctr]--;");
  } else if (ch == '[') {
    WRITEFILE(arq_out, "");
    WRITEFILE(arq_out, "while (arr[ctr] != 0) {");
  } else if (ch == ']') {
    WRITEFILE(arq_out, "}");
    WRITEFILE(arq_out, "");
  } else if (ch == '.') {
    WRITEFILE(arq_out, "letra = arr[ctr];");
    WRITEFILE(arq_out, "printf(\"%c\", letra);");
    WRITEFILE(arq_out, "letra = 'a' - 'a';");
  }
}

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  checkFile(input, "Arquivo nao encontrado");

  FILE *out = fopen("output.c", "w");
  checkFile(out, "Erro ao criar o arquivo");

  boilerplate(out);

  // A maior parte da logica reside neste loop

  FLOOP(input) { escrevendo(ch, out); }

  boilerplate2(out);

  fclose(input);
  fclose(out);

  return 0;
}
