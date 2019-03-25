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
int verificaDisponibilidade(evento a, evento b);

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
    int i, j, c, size = 0, teste = 1;
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
    a.inicio = atoi(descricao[2]);
    a.duracao = atoi(descricao[3]);
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

    for (i = 0; i < SALAS; i ++){
        for (j = 0; j < EVENTOS; j ++){
            if(verificaDisponibilidade(a, reservaSalas[i][j]) == 0){
                teste = 0;
            }  
        }
    }

    if(teste){
        strcpy(reservaSalas[a.sala][numEventos].descricao, a.descricao);
        reservaSalas[a.sala][numEventos].dia = a.dia;
        reservaSalas[a.sala][numEventos].duracao = a.duracao;
        reservaSalas[a.sala][numEventos].inicio = a.inicio;
        reservaSalas[a.sala][numEventos].sala = a.sala;
        strcpy(reservaSalas[a.sala][numEventos].responsavel, a.responsavel);
        strcpy(reservaSalas[a.sala][numEventos].participante_um, a.participante_um);
        strcpy(reservaSalas[a.sala][numEventos].participante_dois, a.participante_dois);
        strcpy(reservaSalas[a.sala][numEventos].participante_tres, a.participante_tres);
        printf("%s\n", reservaSalas[a.sala][numEventos].descricao);
    }
    return; 

}

int duracaoParaHora(evento a){
    int hora = a.inicio;
    int minutos = a.duracao;
    if (a.duracao == 60){
        hora = hora + 100;
    } else {
        minutos = minutos + (hora%100);
        if (minutos >= 60){
            hora = hora + 40 + a.duracao;        
        }
    }
    return hora;
}

int verificaDisponibilidade(evento a, evento b){
    int teste = 1;

    if(!strcmp(a.responsavel, b.responsavel) || !strcmp(a.responsavel, b.participante_um) ||
    !strcmp(a.responsavel, b.participante_dois) || !strcmp(a.responsavel, b.participante_tres)){
        if(a.dia == b.dia && a.inicio <= duracaoParaHora(b)){
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
            teste = 0;
        }
    }

    if(!strcmp(a.participante_um, b.responsavel) || !strcmp(a.participante_um, b.participante_um) || 
    !strcmp(a.participante_um, b.participante_dois) || !strcmp(a.participante_um, b.participante_tres)){
        if(a.dia == b.dia && a.inicio <= duracaoParaHora(b)){
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_um);
            teste = 0;
        }
    }
    
    if (a.numParticipantes == 3){
        if(!strcmp(a.participante_tres, b.participante_dois) || !strcmp(a.participante_tres, b.participante_tres)|| 
        !strcmp(a.participante_tres, b.participante_um) || !strcmp(a.participante_tres, b.responsavel)){
            if(a.dia == b.dia && a.inicio <= duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_dois);
                teste = 0;
            }
        }

        if(!strcmp(a.participante_dois, b.participante_dois) || !strcmp(a.participante_dois, b.participante_tres) ||
        !strcmp(a.participante_dois, b.participante_um) || !strcmp(a.participante_dois, b.responsavel)){
            if(a.dia == b.dia && a.inicio <= duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_tres);
                teste = 0;
            }
        }
    }

    if(a.numParticipantes == 2){
        if(!strcmp(a.participante_tres, b.participante_dois) || !strcmp(a.participante_tres, b.participante_tres)|| 
        !strcmp(a.participante_tres, b.participante_um) || !strcmp(a.participante_tres, b.responsavel)){
            if(a.dia == b.dia && a.inicio <= duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_dois);
                teste = 0;
            }
        }
    }
    return teste;
}

