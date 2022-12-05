#include <stdio.h>
#include <stdlib.h>

int tema; char temaEscolhido[20], novaPalavra[10];

void recebePalavra() {
    do{
        printf("\nQual o tema da nova palavra?\n");
        printf("[1] - Animais\n");
        printf("[2] - Frutas\n");
        printf("[3] - Objetos\n");
        printf("Escolha o tema: ");
        scanf("%d", &tema);

        if(tema != 1 && tema != 2 && tema != 3)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(tema != 1 && tema != 2 && tema != 3);

    do{
        printf("A palavra deve ser de 5 à 7 letras.\n");
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        if(strlen(novaPalavra) != 5 && strlen(novaPalavra) != 6 && strlen(novaPalavra) != 7)
            printf("\nTamanho da palavra inválido! Tente novamente\n");

    } while(strlen(novaPalavra) != 5 && strlen(novaPalavra) != 6 && strlen(novaPalavra) != 7);

    switch(tema){
        case 1:
            if(strlen(novaPalavra) == 5)
                strcpy(temaEscolhido, "temas/animais5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(temaEscolhido, "temas/animais6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(temaEscolhido, "temas/animais7L.txt");
                break;
        case 2:
            if(strlen(novaPalavra) == 5)
                strcpy(temaEscolhido, "temas/frutas5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(temaEscolhido, "temas/frutas6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(temaEscolhido, "temas/frutas7L.txt");
                break;
        case 3:
            if(strlen(novaPalavra) == 5)
                strcpy(temaEscolhido, "temas/objetos5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(temaEscolhido, "temas/objetos6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(temaEscolhido, "temas/objetos7L.txt");
                break;  
        default:
            printf("Opção inválida! Tente novamente\n\n");
    }
}

void adicionaPalavra() {
    FILE* arquivo;

    arquivo = fopen(temaEscolhido, "r+");   // Abro o arquivo com base na escolha do usuario

    int qtd;
    fscanf(arquivo, "%d", &qtd);            // Descubro a qtd de palavras do meu arquivo e adiciono 1
    qtd++;

    fseek(arquivo, 0, SEEK_SET);            // Aponto a seta para o inicio do arquivo e sobrescrevo a qtd
    fprintf(arquivo, "%d", qtd);

    fseek(arquivo, 0, SEEK_END);            // Aponto a seta para o fim do arquivo e adiciono a nova palavra
    fprintf(arquivo, "\n%s", novaPalavra);

    fclose(arquivo);
}