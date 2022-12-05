#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "creditos/creditos.c"
#include "cadastraPalavra.c"
#include "ranking.c"

void menu();
void abertura();
int escolheTema(int numLetras);
void escolhePalavra(char temaEscolhido[20]);
void chuta();
int letraExiste(char letra);
int jaChutou(char letra);
int chutesErrados();
int ganhou();
int enforcou();
void desenhaForca();