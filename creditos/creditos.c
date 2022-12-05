#include <stdio.h>
#include <stdlib.h>

void creditos() {
    char creditos[41];

    FILE* arquivo;

    arquivo = fopen("creditos/creditos.txt", "r");
    if(arquivo == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    printf("\n");

    while(fgets(creditos, 40, arquivo) != NULL){    // Printa as linhas até que seja nulo
        printf("%s", creditos);
    }
    
    printf("\n\n");
    fclose(arquivo);
}