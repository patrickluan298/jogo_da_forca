#include <stdio.h>
#include <stdlib.h>

void salvarJogadorRanking(int pontos, char nome[20]) {
    
    FILE* arquivo;

    arquivo = fopen("ranking/ranking.txt", "r+");

    fseek(arquivo, 0, SEEK_END);

    // fprintf(arquivo, "PONTOS\t-  NOMES\n");
    fprintf(arquivo, "  %d\t-  %s\n", pontos, nome);

    fclose(arquivo);
}

void verRanking() {
    char ranking[41];

    FILE* arquivo;

    arquivo = fopen("ranking/ranking.txt", "r");
    if(arquivo == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    printf("\n");

    while(fgets(ranking, 40, arquivo) != NULL){
        printf("%s", ranking);
    }
    
    printf("\n\n");
    fclose(arquivo);
}