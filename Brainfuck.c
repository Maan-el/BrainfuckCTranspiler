#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int OPENINGERROR = 1;

/*Escrever o \n manualmente e chato ******************************************/
void WRITEFILE(FILE *arquivo, char *texto) { fprintf(arquivo, "%s\n", texto); }

/*Testa se o arquivo abriu sem nenhum problema *******************************/
void checkFile(FILE *arquivo, char *mensagem) {
  if (arquivo == NULL) {
    fprintf(stderr, "%s\n", mensagem);
    exit(OPENINGERROR);
  }
}

/*Nao esta sendo usado ainda *************************************************/
int sizeofFile(FILE *arquivo) {
  int size, safesize;

  while (!feof(arquivo)) {
    size++;
  }
  // Tamanho incluindo o \n e o \0
  safesize = size + 2;
  return safesize;
}

// Rewirint stuff
unsigned int furtherMostChar(FILE *input, char busca) {
  char ch;
  unsigned int max;

  while (!feof(input)) {
    ch = fgetc(input);
    if (ch == busca) {
      max++;
    }
  }
  return max;
}

unsigned int sizeofFileArray(FILE *input) {
  unsigned int num_right_mov = furtherMostChar(input, '>');
  unsigned int num_left_mov = furtherMostChar(input, '<');

  if (num_right_mov > num_left_mov) {
    return num_right_mov - num_left_mov;
  } else {
    return num_left_mov - num_right_mov;
  }
}

/*Base do arquivo ************************************************************/
void boilerplate(FILE *arq_out) {
  WRITEFILE(arq_out, "#include <stdio.h>");
  WRITEFILE(arq_out, "");
  WRITEFILE(arq_out, "int main (void) {");
  fprintf(arq_out, "int arr[%d];\n", sizeofFileArray(arq_out));
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
  char c;

  FILE *input = fopen(argv[1], "r");
  checkFile(input, "Arquivo nao encontrado");

  FILE *out = fopen("output.c", "w");
  checkFile(out, "Erro ao criar o arquivo");

  boilerplate(out);

  // A maior parte da logica reside neste loop

  while (!feof(input)) {
    c = fgetc(input);
    escrevendo(c, out);
  }

  boilerplate2(out);

  fclose(input);
  fclose(out);

  return 0;
}
