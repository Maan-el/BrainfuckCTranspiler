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
  escreveArq(arqOut, "int arr[30000], ctr;");
  escreveArq(arqOut, "char letra;");
  escreveArq(arqOut, "");
}

void escrevendo(char ch, FILE *arqOut) {
  if (ch == '+') {
    escreveArq(arqOut, "arr[ctr]++;");
  } else if (ch == '>') {
    escreveArq(arqOut, "ctr++;");
  } else if (ch == '<') {
    escreveArq(arqOut, "ctr--;");
  } else if (ch == '-') {
    escreveArq(arqOut, "arr[ctr]--;");
  } else if (ch == '[') {
    escreveArq(arqOut, "");
    escreveArq(arqOut, "while (arr[ctr] != 0) {");
  } else if (ch == ']') {
    escreveArq(arqOut, "}");
    escreveArq(arqOut, "");
  } else if (ch == '.') {
    escreveArq(arqOut, "letra = arr[ctr];");
    escreveArq(arqOut, "printf(\"%c\", letra);");
    escreveArq(arqOut, "letra = 'a' - 'a';");
  }
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
    escrevendo(c, out);
  }

  escreveArq(out, "");
  escreveArq(out, "return 0;");
  escreveArq(out, "}");

  fclose(input);
  fclose(out);

  return 0;
}
