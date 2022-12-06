#include "forca.h"

typedef struct  {
    char nome[20];
    int pontos;
}stJogadores;

void nomeJogadores(char *nome) {
    printf("Nome do jogador: ");
    scanf("%s", nome);
    return;
}

void menu() {
    int escolha;

    do{
        printf("/###########################/\n");
        printf("/#      Jogo da Forca      #/\n");
        printf("/###########################/\n\n");

        printf("[1] - Jogar\n");
        printf("[2] - Ver Ranking\n");
        printf("[3] - Cadastrar palavra\n");
        printf("[4] - Créditos\n");
        printf("[0] - Sair\n");
        printf("Escolha a opção: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                printf("Iniciando jogo...\n\n");
                break;
            case 2:
                verRanking();
                menu();
                break;
            case 3:
                recebePalavra();
                menu();
                break;
            case 4:
                creditos();
                menu();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Opção inválida! Tente novamente\n\n");
        }
    } while(escolha != 0 && escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4);
}

void abertura(int *qntJogadores, int *qntLetras) {
    do{
        printf("Número de jogadores: ");
        scanf("%d", qntJogadores);

        if(*qntJogadores < 1 || *qntJogadores > 10)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(*qntJogadores < 1 || *qntJogadores > 10);

    do{
        printf("Escolha a quantidade de letras (5, 6, 7): ");
        scanf("%d", qntLetras);

        if(*qntLetras != 5 && *qntLetras!= 6 && *qntLetras != 7)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(*qntLetras != 5 && *qntLetras!= 6 && *qntLetras != 7);
}

void escolheTema(char *tema, int numLetras) {
    int escolha;

    do {
        printf("\n####### TEMAS DO JOGO #######\n");
        printf("[1] - Animais\n");
        printf("[2] - Frutas\n");
        printf("[3] - Objetos\n");
        printf("Escolha o tema: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if(numLetras == 5)
                    strcpy(tema, "temas/animais5L.txt");     // strcpy(): Armazena uma string numa variável string
                else if(numLetras == 6)
                    strcpy(tema, "temas/animais6L.txt");
                else if(numLetras == 7)
                    strcpy(tema, "temas/animais7L.txt");
                break;
            case 2:
                if(numLetras == 5)
                    strcpy(tema, "temas/frutas5L.txt");
                else if(numLetras == 6)
                    strcpy(tema, "temas/frutas6L.txt");
                else if(numLetras == 7)
                    strcpy(tema, "temas/frutas7L.txt");
                break;
            case 3:
                if(numLetras == 5)
                    strcpy(tema, "temas/objetos5L.txt");
                else if(numLetras == 6)
                    strcpy(tema, "temas/objetos6L.txt");
                else if(numLetras == 7)
                    strcpy(tema, "temas/objetos7L.txt");
                break;  
            default:
                printf("Opção inválida! Tente novamente\n\n");
        }
    } while(escolha != 1 && escolha != 2 && escolha != 3);

    return;
}

void escolhePalavra(char *tema, char *palavraSecreta) {
    int i, qtdDePalavras, randomico;
    
    FILE* arquivo;

    arquivo = fopen(tema, "r");    // Abre o arquivo com base na escolha do usuário
    if(arquivo == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &qtdDePalavras);

    srand(time(0));
    randomico = rand() % qtdDePalavras;

    for(i = 0; i <= randomico; i++) {
        fscanf(arquivo, "%s", palavraSecreta);
    }

    fclose(arquivo);
}

void chuta(char *palavraSecreta, char *chutes, int *qntChutesDados) {
    char chute;

    printf("Qual a letra? ");
    scanf(" %c", &chute);
    chute = toupper(chute);

    if(letraExiste(palavraSecreta, chute)) {
        printf("Você acertou! A palavra tem a letra '%c'\n\n", chute);
    } else {
        printf("\nVocê errou! A palavra não tem a letra '%c'\n\n", chute);
    }

    chutes[*qntChutesDados] = chute;
    (*qntChutesDados)++;
    return;
}

int letraExiste(char *palavraSecreta, char letra) {
    for(int j = 0; j < strlen(palavraSecreta); j++) {
        if(letra == palavraSecreta[j]) {
            return 1;
        }
    }
    return 0;
}

int verificaLetraNaPalavra(char letra, char *chutes) {
    int achou = 0;
    for(int j = 0; j < strlen(chutes); j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

int calculaChutesErrados(char *palavraSecreta, char *chutes) {
    int pontos = 5;

    for(int i = 0; i < strlen(chutes); i++)
        if(!letraExiste(palavraSecreta, chutes[i]))
            pontos--;

    return pontos;
}

int ganhou(char *palavraSecreta, char *chutes) {
    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(!verificaLetraNaPalavra(palavraSecreta[i], chutes)) {
            return 0;
        }
    }
    return 1;
}

int enforcou(char *palavraSecreta, char *chutes) {
    return calculaChutesErrados(palavraSecreta, chutes) == 0;
}

void desenhaForca(char *palavraSecreta, char *chutes) {
    int pontos = calculaChutesErrados(palavraSecreta, chutes);

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (pontos<=4?'(':' '), (pontos<=4?'_':' '), (pontos<=4?')':' '));
    printf(" |      %c%c%c  \n", (pontos<=2?'\\':' '), (pontos<=3?'|':' '), (pontos<=2?'/': ' '));
    printf(" |       %c     \n", (pontos<=3?'|':' '));
    printf(" |      %c %c   \n", (pontos<=1?'/':' '), (pontos<=1?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavraSecreta); i++) {       // strlen(): Calcula a quantidade de caracteres de uma string
        if(verificaLetraNaPalavra(palavraSecreta[i], chutes)) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\n");
    return;
}

void imprimirVencedor(char *palavraSecreta){
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    Parabéns, você ganhou!\n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'    A palavra era %s.\n", palavraSecreta);
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}

void imprimirPerdedor(char *palavraSecreta){
    printf("          ⠀⠀⢀⡤⠄⠒⠒⠢⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀     \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢞⠏⠀⠀⠀⠀⠀⠀⠈⢢⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⡎⢀⠄⠀⣀⠀⠀⣀⠀⠄⡇⠀⠀⠀⠀⠀⠀⠀  \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⢃⢂⣴⣿⣿⡧⢸⣿⣷⢨⠃⠀⠀⠀⠀⠀⠀⠀⠀  \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⠂⠙⢿⣿⣷⡾⡛⠋⢪⠀⠀⠀⠀⠀⠀⠀⠀   Oh não, você foi enforcado!\n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⢺⣧⣀⣀⣠⣿⠒⠋⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠉⠻⠿⠋⠉⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀   A palavra era %s.\n", palavraSecreta);
    printf(" ⠀⢶⣤⣄⣶⠀⠀⠀⠀⠀⢀⣤⣾⣶⣶⡶⢾⣷⢶⡟⡆⠀⠀⢰⣀⣤⣤⠄   \n");
    printf(" ⠐⢛⣿⣿⡿⣤⣄⡀⠀⡀⢊⢼⢽⡿⢿⢹⠷⠶⠝⡷⠜⠄⣀⢸⣿⣿⡻⠃   \n");
    printf(" ⠀⠻⠋⠀⠁⠒⠠⠭⢇⡐⠁⠘⠩⣬⠛⣶⣇⠐⣿⠁⠘⢮⣕⠜⠁⠀⠁⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠉⢁⡿⠛⢉⡄⡹⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⠦⠀⠀⡀⠀⢺⠳⠤⠄⢤⡀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢎⠜⠒⠉⠈⠁⠉⢉⣩⢏⣾⠇⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣋⣎⠀⠀⠀⠀⡤⣤⢟⠟⠁⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢴⠺⣄⠀⠀⠀⠀⢸⡑⡁⠀⠀⠀⠀⠀⠀⠀⠀  \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⣙⠢⡄⠀⠀⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⢗⢻⠝⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠮⠕⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n\n");
}

void iniciarForca(int qntLetras){
    char tema[20] = "", palavraSecreta[10] = "", chutes[26] = "";
    int qntChutesDados = 0;
    stJogadores jogadores;

    memset(&jogadores, 0, sizeof(stJogadores));

    escolheTema(tema, qntLetras);
    escolhePalavra(tema, palavraSecreta);
    nomeJogadores(jogadores.nome);
    
    do {
        desenhaForca(palavraSecreta, chutes);
        chuta(palavraSecreta, chutes, &qntChutesDados);

    } while (!ganhou(palavraSecreta, chutes) && !enforcou(palavraSecreta, chutes));

    if(ganhou(palavraSecreta, chutes)) 
        imprimirVencedor(palavraSecreta);
    else
        imprimirPerdedor(palavraSecreta);

    jogadores.pontos = calculaChutesErrados(palavraSecreta, chutes);
    salvarJogadorRanking(jogadores.pontos, jogadores.nome);
    return;
}

int main() {
    int jogadorDaVez = 0, qntJogadores = 0, qntLetras = 0;

    while(1){
        menu();
        abertura(&qntJogadores, &qntLetras);

        for(jogadorDaVez = 1; jogadorDaVez <= qntJogadores; jogadorDaVez++){
            
            iniciarForca(qntLetras);

            if(jogadorDaVez != qntJogadores)
                printf("\nPróximo jogador\n");
        }
    }

    return(0);
}