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
    int numParticipantes;
} evento;

void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos);
int leValores(int count);
int participantes(evento a);
int duracaoParaHora(evento a);

int main(){

   evento reservaSalas[SALAS][EVENTOS];
   int numEventos = 0;
    
    char opcao;
    opcao = getchar();

    while(opcao != '0'){
        if (opcao == 'a'){
            adicionaEvento(reservaSalas, numEventos);
            numEventos++;
        }
        opcao = getchar();
    }

    
    return 0;
    
}

/*hora inicio do evento 2 >= hora de conclusao do evento 1
não é preciso verificar input*/


void adicionaEvento(evento reservaSalas[SALAS][EVENTOS], int numEventos){

    evento a;
    int c, i, j, numLetras = 0;
    
    while((c = getchar()) != ':'){
        a.descricao[numLetras] = c;
        numLetras ++;        
    }
    a.descricao[numLetras] = '\0';

    a.dia = leValores(10000000);
    a.inicio = leValores(1000);
    a.duracao = leValores(10);
    a.sala = leValores(1);

    numLetras = 0;
    while((c = getchar()) != ':'){
        a.responsavel[numLetras] = c;
        numLetras ++;        
    }
    a.responsavel[numLetras] = '\0';

    numLetras = 0;
    while((c = getchar()) != ':' && c != '\n'){
        a.participante_um[numLetras] = c;
        numLetras ++;   
    }
    a.participante_um[numLetras] = '\0';

    numLetras = 0;
    while(c != '\n' && (c = getchar()) != ':'){
        a.participante_dois[numLetras] = c;
        numLetras ++;   
    }
    a.participante_dois[numLetras] = '\0';

    numLetras = 0;
    while(c != '\n' && (c = getchar()) != ':'){
        a.participante_tres[numLetras] = c;
        numLetras ++;   
    }
    a.participante_tres[numLetras] = '\0';

    for(i = 0; i < EVENTOS; i ++){
        if (a.dia == reservaSalas[a.sala][i].dia && a.sala == reservaSalas[a.sala][i].sala
            && a.inicio <= duracaoParaHora(reservaSalas[a.sala][i])) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            return;
        }

    }

    for(i = 0; i < SALAS; i++){
        for(j = 0; j < EVENTOS; j++){
            if(strcmp(a.responsavel, reservaSalas[i][j].responsavel) == 0){

            }
        }

    }



    getchar();
    reservaSalas[a.sala][numEventos] = a;


}

int leValores(int count){
    int valor = 0, c;
    while((c = getchar()) != ':' ){
        c = c - '0';
        valor = c*count + valor;
        count = count/10;              
    }
    return valor;
}

int participantes(evento a){
    int num = 1;

    if (a.participante_dois[0] != '\0'){
        num ++;
    }
    if (a.participante_tres[0] != '\0'){
        num ++;
    }
    return num;
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
