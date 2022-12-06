#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "creditos/creditos.c"
#include "cadastraPalavra.c"
#include "ranking/ranking.c"

void menu();
void abertura(int *qntJogadores, int *qntLetras);
void escolheTema(char *tema, int numLetras);
void escolhePalavra(char *temaEscolhido, char *palavraSecreta);
void chuta(char *palavraSecreta, char *chutes, int *qntChutesDados);
int letraExiste(char *palavraSecreta, char letra);
int verificaLetraNaPalavra(char letra, char *chutes);
int calculaChutesErrados(char *palavraSecreta, char *chutes);
int ganhou(char *palavraSecreta, char *chutes);
int enforcou(char *palavraSecreta, char *chutes);
void desenhaForca(char *palavraSecreta, char *chutes);