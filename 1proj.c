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

/*a descricao:data:inicio:duracao:sala:responsavel:participantes*/
/*a Reuniao dos Ze:29032019:1000:60:1:Ze:Ze Carlos:Ze Pedro:Ze Joao*/
void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos){

    evento a;
    int c, numLetras = 0, count = 10000000, data = 0, hora = 0, duracao = 0;
    
    while((c = getchar()) != ':' && numLetras < 63 ){
        a.descricao[numLetras] = c;
        numLetras ++;        
    }
    a.descricao[numLetras] = '\0';

    while((c = getchar()) != ':' ){
        c = c - '0';
        data = c*count + data;
        count = count/10;              
    }
    a.dia = data;

    count = 1000;
    while((c = getchar()) != ':' ){
        c = c - '0';
        hora = c*count + hora;
        count = count/10;              
    }
    a.inicio = hora;

    count = 10;
    while((c = getchar()) != ':' ){
        c = c - '0';
        duracao = c*count + duracao;
        count = count/10;              
    }
    a.duracao = duracao;

    a.sala = getchar();
    a.sala = a.sala - '0';
    getchar();

    numLetras = 0;
    while((c = getchar()) != ':' && numLetras < 63 ){
        a.responsavel[numLetras] = c;
        numLetras ++;        
    }
    a.responsavel[numLetras] = '\0';

    numLetras = 0;
    while((c = getchar()) != ':' && numLetras < 63 && c != '\n'){
        a.participante_um[numLetras] = c;
        numLetras ++;   
    }
    a.participante_um[numLetras] = '\0';

    numLetras = 0;
    while(c != '\n' && numLetras < 63 && (c = getchar()) != ':'){
        a.participante_dois[numLetras] = c;
        numLetras ++;   
    }
    a.participante_dois[numLetras] = '\0';

    numLetras = 0;
    while(c != '\n' && numLetras < 63 && (c = getchar()) != ':'){
        a.participante_tres[numLetras] = c;
        numLetras ++;   
    }
    a.participante_tres[numLetras] = '\0';

    printf("%s\n", a.descricao);
    printf("%d\n", a.dia);
    printf("%d\n", a.inicio);
    printf("%d\n", a.duracao);
    printf("%d\n", a.sala);
    printf("%s\n", a.responsavel);
    printf("%s\n", a.participante_um);
    /*printf("%s\n", a.participante_dois);
    printf("%s\n", a.participante_tres);*/
}
