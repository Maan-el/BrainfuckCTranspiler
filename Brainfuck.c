#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkFile(FILE *nome, char *mensagem) {
  if (nome == NULL) {
    fprintf(stderr, "%s\n", mensagem);
    exit(1);
  }
}

/*Escrever o \n manualmente deixa o cdigo feio********************************/
void escreveArq(FILE *input, char *texto) { fprintf(input, "%s\n", texto); }

/*Base do arquivo*************************************************************/
void boilerplate(FILE *out) {
  escreveArq(out, "#include <stdio.h>");
  escreveArq(out, "");
  escreveArq(out, "int main (void) {");
  escreveArq(out, "int arr[30000];");
}

int main(void) {
  FILE *input = fopen("bainfuck", "r");
  checkFile(input, "Arquivo nao encontrado");

  FILE *out = fopen("output.c", "w");
  checkFile(out, "Erro ao criar o arquivo");

  boilerplate(out);

  fclose(input);
  fclose(out);

  return 0;
}
