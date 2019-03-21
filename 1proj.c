#include <stdio.h>
#include <string.h>

#define SALAS 10
#define EVENTOS 100
#define MAXIMO_NOME 63

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
} evento;

void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos);

int main(){

   evento reservaSalas[SALAS][EVENTOS];
   int numEventos = 0;
    
    char opcao;
    opcao = getchar();

    if (opcao == 'a'){
        adicionaEvento(reservaSalas, numEventos);
        numEventos++;
    }
    return 0;
    
}

void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos){

    evento a;
    int c, numLetras = 0, count = 10000000, data = 0;
    
    while((c = getchar()) != ':' && numLetras < 63 ){
        a.descricao[numLetras] = c;
        numLetras ++;        
    }

    while((c = getchar()) != ':' ){
        c = c - '0';
        data = c*count + data;
        count = count/10;              
    }
    a.dia = data;



    printf("%s\n", a.descricao);
    printf("%d\n", a.dia);
}
