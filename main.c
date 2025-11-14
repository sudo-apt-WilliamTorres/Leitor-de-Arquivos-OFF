#include <stdio.h>
#include "malha.h"

int main() {
    Malha m;
    char nomeArquivo[100];

    printf("Digite o nome do arquivo OFF: ");
    scanf("%s", nomeArquivo);

    lerOFF(nomeArquivo, &m);

    imprimirMalha(&m);

    liberarMalha(&m);

    return 0;
}
