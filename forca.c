#include "forca.h"

// Variáveis globais
char palavraSecreta[10], temaEscolhido[20], chutes[26];
int numJogadores, numLetras, chutesDados = 0;

struct jogadores {
    char nome[20];
    int pontos;
};
struct jogadores jogadores;

void nomeJogadores() {
    printf("Nome do jogador: ");
    scanf("%s", jogadores.nome);
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
        printf("Escolha o tema: ");
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

void abertura() {
    do{
        printf("Número de jogadores: ");
        scanf("%d", &numJogadores);

        if(numJogadores < 1 || numJogadores > 10)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(numJogadores < 1 || numJogadores > 10);

    do{
        printf("Escolha a quantidade de letras (5, 6, 7): ");
        scanf("%d", &numLetras);

        if(numLetras != 5 && numLetras!= 6 && numLetras != 7)
            printf("\nOpção Inválida! Tente Novamente\n");

    } while(numLetras != 5 && numLetras!= 6 && numLetras != 7);
}

int escolheTema(int numLetras) {
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
                    strcpy(temaEscolhido, "temas/animais5L.txt");     // strcpy(): Armazena uma string numa variável string
                else if(numLetras == 6)
                    strcpy(temaEscolhido, "temas/animais6L.txt");
                else if(numLetras == 7)
                    strcpy(temaEscolhido, "temas/animais7L.txt");
                break;
            case 2:
                if(numLetras == 5)
                    strcpy(temaEscolhido, "temas/frutas5L.txt");
                else if(numLetras == 6)
                    strcpy(temaEscolhido, "temas/frutas6L.txt");
                else if(numLetras == 7)
                    strcpy(temaEscolhido, "temas/frutas7L.txt");
                break;
            case 3:
                if(numLetras == 5)
                    strcpy(temaEscolhido, "temas/objetos5L.txt");
                else if(numLetras == 6)
                    strcpy(temaEscolhido, "temas/objetos6L.txt");
                else if(numLetras == 7)
                    strcpy(temaEscolhido, "temas/objetos7L.txt");
                break;  
            default:
                printf("Opção inválida! Tente novamente\n\n");
        }
    } while(escolha != 1 && escolha != 2 && escolha != 3);
}

void escolhePalavra(char temaEscolhido[20]) {
    int i, qtdDePalavras, randomico;
    
    FILE* arquivo;

    arquivo = fopen(temaEscolhido, "r");    // Abre o arquivo com base na escolha do usuário
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

void chuta() {
    char chute;

    printf("Qual a letra? ");
    scanf(" %c", &chute);
    chute = toupper(chute);

    if(letraExiste(chute)) {
        printf("Você acertou! A palavra tem a letra '%c'\n\n", chute);
    } else {
        printf("\nVocê errou! A palavra não tem a letra '%c'\n\n", chute);
    }

    chutes[chutesDados] = chute;
    chutesDados++;
}

int letraExiste(char letra) {
    for(int j = 0; j < strlen(palavraSecreta); j++) {
        if(letra == palavraSecreta[j]) {
            return 1;
        }
    }
    return 0;
}

int jaChutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

int chutesErrados() {
    int pontos = 5;

    printf("ENTROU NO CHUTES ERRADOS\n");

    for(int i = 0; i < chutesDados; i++) {
        if(!letraExiste(chutes[i])) {
            pontos--;
            printf("PONTOS INTERNO: %d\n", pontos);
        }
    }

    printf("PONTOS: %d\n", pontos);
    return pontos;
}

int ganhou() {
    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int enforcou() {
    return chutesErrados() == 0;
}

void desenhaForca() {
    int pontos = chutesErrados();

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
        if(jaChutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    int i, opcao;

    menu();
    abertura();

    for(i = 0; i < numJogadores; i++){
        if(i > 0){
            printf("\nPróximo jogador\n");
        }
        escolheTema(numLetras);
        escolhePalavra(temaEscolhido);
        nomeJogadores();
        
        do {
            desenhaForca();
            chuta();

        } while (!ganhou() && !enforcou());

        if(ganhou()) {
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

        }else{
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
        chutesDados = 0;

        jogadores.pontos = chutesErrados();
        cadastroJogadores(jogadores.pontos, jogadores.nome);
    }
    menu();

    return(0);
}