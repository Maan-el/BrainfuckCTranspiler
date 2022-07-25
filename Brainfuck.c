#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkFile(FILE *nome, char *mensagem) {
  if (nome == NULL) {
    fprintf(stderr, "%s\n", mensagem);
    exit(1);
  }
}

/*Escrever o \n manualmente e chato ******************************************/
void escreveArq(FILE *input, char *texto) { fprintf(input, "%s\n", texto); }

/*Base do arquivo ************************************************************/
void boilerplate(FILE *arqOut) {
  escreveArq(arqOut, "#include <stdio.h>");
  escreveArq(arqOut, "");
  escreveArq(arqOut, "int main (void) {");
  escreveArq(arqOut, "int arr[30000];");
  escreveArq(arqOut, "int ptr = 0;");
}

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  checkFile(input, "Arquivo nao encontrado");

  FILE *out = fopen("output.c", "w");
  checkFile(out, "Erro ao criar o arquivo");

  boilerplate(out);

  char c;
  while (!feof(input)) {
    c = fgetc(input);
    if (c == '+') {
      escreveArq(out, "arr[ptr]++;");
    } else if (c == '>') {
      escreveArq(out, "ptr++;");
    } else if (c == '<') {
      escreveArq(out, "ptr--");
    } else if (c == '-') {
      escreveArq(out, "arr[ptr]--;");
    }
  }

  fclose(input);
  fclose(out);

  return 0;
}
