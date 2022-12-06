#include <stdio.h>
#include <stdlib.h>

void adicionaPalavra(char *tema, char *novaPalavra) {
    FILE* arquivo;

    arquivo = fopen(tema, "r+");                        // Abro o arquivo com base na escolha do usuario

    int qnt;
    fscanf(arquivo, "%d", &qnt);                        // Descubro a qnt de palavras do meu arquivo e adiciono 1
    qnt++;

    fseek(arquivo, 0, SEEK_SET);                        // Aponto a seta para o inicio do arquivo e sobrescrevo a qnt
    fprintf(arquivo, "%d", qnt);

    fseek(arquivo, 0, SEEK_END);                        // Aponto a seta para o fim do arquivo e adiciono a nova palavr
    if(fprintf(arquivo, "\n%s", novaPalavra))
        printf("\nPalavra cadastrada com sucesso!\n\n");
    else
        printf("\nErro ao cadastrar a palavra!\n\n");

    fclose(arquivo);
}

void recebePalavra() {
    int escolha, i = 0; char novaPalavra[7], tema[20];

    do{
        printf("\nQual o tema da nova palavra?\n");
        printf("[1] - Animais\n");
        printf("[2] - Frutas\n");
        printf("[3] - Objetos\n");
        printf("Escolha o tema: ");
        scanf("%d", &escolha);

        if(escolha != 1 && escolha != 2 && escolha != 3)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(escolha != 1 && escolha != 2 && escolha != 3);

    do{
        printf("\nA palavra deve ser de 5 à 7 letras.\n");
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        while(novaPalavra[i] != '\0'){
            novaPalavra[i] = toupper(novaPalavra[i]);
            i++;
        }
        novaPalavra[i] = '\0';

        if(strlen(novaPalavra) != 5 && strlen(novaPalavra) != 6 && strlen(novaPalavra) != 7)
            printf("\nTamanho da palavra inválido! Tente novamente\n");

    } while(strlen(novaPalavra) != 5 && strlen(novaPalavra) != 6 && strlen(novaPalavra) != 7);

    switch(escolha){
        case 1:
            if(strlen(novaPalavra) == 5)
                strcpy(tema, "temas/animais5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(tema, "temas/animais6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(tema, "temas/animais7L.txt");
                break;
        case 2:
            if(strlen(novaPalavra) == 5)
                strcpy(tema, "temas/frutas5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(tema, "temas/frutas6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(tema, "temas/frutas7L.txt");
                break;
        case 3:
            if(strlen(novaPalavra) == 5)
                strcpy(tema, "temas/objetos5L.txt");
            else if(strlen(novaPalavra) == 6)
                strcpy(tema, "temas/objetos6L.txt");
            else if(strlen(novaPalavra) == 7)
                strcpy(tema, "temas/objetos7L.txt");
                break;  
        default:
            printf("Opção inválida! Tente novamente\n\n");
    }

    adicionaPalavra(tema, novaPalavra);
}