#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALAS 10
#define EVENTOS 100
#define MAXIMO_NOME 63
#define MAX 340

typedef struct {
    char descricao[MAXIMO_NOME];
    int dia;
    int inicio;
    int duracao;
    int sala;
    char responsavel[MAXIMO_NOME];
    char participante_um[MAXIMO_NOME];
    char participante_dois[MAXIMO_NOME];
    char participante_tres[MAXIMO_NOME];
    int numParticipantes;
} evento;

void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos);
int duracaoParaHora(evento a);

int main(){
    evento reservaSalas[SALAS][EVENTOS];
   int numEventos = 0;
    
    char opcao;
    opcao = getchar();

    while(opcao != 'x'){
        if (opcao == 'a'){
            getchar();
            adicionaEvento(reservaSalas, numEventos);
            numEventos++;
        }
        opcao = getchar();
    }

    
    return 0;
}

void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos){
    
    char texto[MAX];
    char descricao[9][MAXIMO_NOME];
    char *token;
    int i, c, size = 0;
    evento a;

    c = getchar();
    for(i = 0; i < MAX-1 && c != EOF && c != '\n'; i++){
        texto[i] = c;
        c = getchar();
    }

    i = 0;
    token = strtok(texto, ":");
    while( token != NULL ) {
        strcpy(descricao[i], token);
        token = strtok(NULL, ":"); 
        size ++;
        i ++;
    }

    a.numParticipantes = size - 6;
    strcpy(a.descricao, descricao[0]);
    a.dia = atoi(descricao[1]);
    a.duracao = atoi(descricao[2]);
    a.inicio = atoi(descricao[3]);
    a.sala = atoi(descricao[4]);
    strcpy(a.responsavel, descricao[5]);
    strcpy(a.participante_um, descricao[6]);
    if (a.numParticipantes == 3){
        strcpy(a.participante_dois, descricao[7]);
        strcpy(a.participante_tres, descricao[8]);
    }
    if (a.numParticipantes == 2) {
        strcpy(a.participante_dois, descricao[7]);
    }

    for(i = 0; i < EVENTOS; i ++){
        if (a.sala == reservaSalas[a.sala][i].sala && a.dia == reservaSalas[a.sala][i].dia && 
            a.inicio <= duracaoParaHora(reservaSalas[a.sala][i])) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            return;
        }

    }
    reservaSalas[a.sala][numEventos] = a;

}

int duracaoParaHora(evento a){
    int i = a.inicio%100 + a.duracao;
    int hora = 0;
    if (i > 60 || i == 60){
        hora = (a.inicio + 100) + (i - 60);
    } else {
        hora = a.inicio + a.duracao;
    }
    return hora;
}

