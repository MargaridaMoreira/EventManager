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

void adicionaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos);
void listaSala(int sala, evento reservaSalas[SALAS*EVENTOS], int numEventos);
void listaEvento(evento reservaSalas[SALAS*EVENTOS],int numEventos);
void apagaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos);
void alteraInicio(evento reservaSalas[EVENTOS*SALAS], int numEventos);
int duracaoParaHora(evento a);
int verificaEvento(evento a, evento reservaSalas[SALAS*EVENTOS], int numEventos, int indice);
int verificaDisponibilidade(evento a, evento b);
int ordenaData(evento a);
void ordenaEventos(evento reservaSalas[SALAS*EVENTOS], int numEventos);
int procuraDescricao(char descricao[MAXIMO_NOME], evento reservaSalas[SALAS*EVENTOS], int numEventos);

int main(){
    evento reservaSalas[SALAS * EVENTOS];
    int numEventos = 0, sala;
    
    char opcao;
    opcao = getchar();

    while(opcao != 'x'){
        switch(opcao){
            case 'a':
                    getchar();
                    adicionaEvento(reservaSalas, &numEventos);
                    break;
            case 's':
                    getchar();
                    scanf("%d", &sala);
                    listaSala(sala, reservaSalas, numEventos);
                    break;
            case 'l':
                    getchar();
                    listaEvento(reservaSalas, numEventos);
                    break;
            case 'r':
                    getchar();
                    apagaEvento(reservaSalas, &numEventos);
                    break;
            case 'i':
                    getchar();
                    alteraInicio(reservaSalas, numEventos);
                    break;
            default:
                    break;
        }
        opcao = getchar();
    }
    return 0;
}

void adicionaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos){
    
    char texto[MAX], descricao[9][MAXIMO_NOME] = {0}, *token;
    int i, c, size = 0, teste = 1;
    evento a;

    c = getchar();
    for(i = 0; i < MAX-1 && c != EOF && c != '\n'; i++){
        texto[i] = c;
        c = getchar();
    }
    texto[i] = '\0';

    i = 0;
    token = strtok(texto, ":\n");
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
    strcpy(a.participante_dois, descricao[7]);
    strcpy(a.participante_tres, descricao[8]);


        for(i = 0; i < (*numEventos); i ++){
            if (a.sala == reservaSalas[i].sala && a.dia == reservaSalas[i].dia && 
                a.inicio <= duracaoParaHora(reservaSalas[i])) {
                    printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
                    return;
                    teste = 0;
            }
    
        }



        for (i = 0; i < (*numEventos); i ++){
            if(verificaDisponibilidade(a, reservaSalas[i]) == 0){
                teste = 0;
            }     
        }
   

    if(teste){
        reservaSalas[(*numEventos)] = a;
        (*numEventos) ++;
    }

    return;
}

void listaSala(int sala, evento reservaSalas[SALAS*EVENTOS],int numEventos){
    int i;
    ordenaEventos(reservaSalas, numEventos);

    for(i = 0; i < numEventos; i ++){
        if(reservaSalas[i].sala == sala){
            printf("%s %d %04d %d Sala%d %s\n", reservaSalas[i].descricao, reservaSalas[i].dia, 
                   reservaSalas[i].inicio, reservaSalas[i].duracao, reservaSalas[i].sala, reservaSalas[i].responsavel);
            printf("* %s %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois, 
                   reservaSalas[i].participante_tres);
        }
    }
    return;  
}

void listaEvento(evento reservaSalas[SALAS*EVENTOS],int numEventos){
    int i;
    ordenaEventos(reservaSalas, numEventos);
    for(i = 0; i < numEventos; i ++){
        printf("%s %d %04d %d Sala%d %s\n", reservaSalas[i].descricao, reservaSalas[i].dia, 
               reservaSalas[i].inicio, reservaSalas[i].duracao, reservaSalas[i].sala, reservaSalas[i].responsavel);
        printf("* %s %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois, 
               reservaSalas[i].participante_tres);
    }
    return;  
}

void apagaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos){
    char descricao[MAXIMO_NOME];
    int i, c, indice = -1;

    c = getchar();
    for(i = 0; i < MAX-1 && c != EOF && c != '\n'; i++){
        descricao[i] = c;
        c = getchar();
    }
    descricao[i] = '\0';

    indice = procuraDescricao(descricao, reservaSalas, (*numEventos));

    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao);
        return;
    } else {
        memmove(&reservaSalas[indice], &reservaSalas[indice + 1], ((*numEventos)-1) * sizeof(reservaSalas[indice]));
        (*numEventos)--;
    }

}

void alteraInicio(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c;
    char descricao[2][MAXIMO_NOME] = {0}, texto[MAX], *token;
    evento a;

    c = getchar();
    for(i = 0; i < MAX-1 && c != EOF && c != '\n'; i++){
        texto[i] = c;
        c = getchar();
    }
    texto[i] = '\0';

    i = 0;
    token = strtok(texto, ":\n");
    while( token != NULL ) {
        strcpy(descricao[i], token);
        token = strtok(NULL, ":"); 
        i ++;
    }
    
    if(procuraDescricao(descricao[0], reservaSalas, numEventos) == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        a = reservaSalas[procuraDescricao(descricao[0], reservaSalas, numEventos)];
        a.inicio = atoi(descricao[1]);
        if(verificaEvento(a, reservaSalas, numEventos, procuraDescricao(descricao[0], reservaSalas, numEventos))){
            reservaSalas[procuraDescricao(descricao[0], reservaSalas, numEventos)].inicio = atoi(descricao[1]);
        }
    }

    return;
}


int duracaoParaHora(evento a){
    int hora, minutos;
    hora = a.inicio;
    hora = hora + 100*(a.duracao/60) + a.duracao%60;
    minutos = hora%100;
    hora = ((hora/100) + minutos/60) * 100 + (minutos%60);
    return hora;
}

int verificaEvento(evento a, evento reservaSalas[SALAS*EVENTOS], int numEventos, int indice){
    int i, teste = 1;
    for(i = 0; i < numEventos; i ++){
        if (indice != i && a.sala == reservaSalas[i].sala && a.dia == reservaSalas[i].dia && 
            reservaSalas[i].inicio < duracaoParaHora(a)) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            teste = 0;
            return teste;
        }
    }

    for (i = 0; i < numEventos; i ++){
        if(indice != i && verificaDisponibilidade(a, reservaSalas[i]) == 0){
            teste = 0;
            break;
        }  
    }
    return teste;

}

int verificaDisponibilidade(evento a, evento b){
    int teste = 1;

    if(!strcmp(a.responsavel, b.responsavel) || !strcmp(a.responsavel, b.participante_um) ||
    !strcmp(a.responsavel, b.participante_dois) || !strcmp(a.responsavel, b.participante_tres)){
        if(a.dia == b.dia && a.inicio < duracaoParaHora(b)){
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
            teste = 0;
        }
    }

    if(!strcmp(a.participante_um, b.responsavel) || !strcmp(a.participante_um, b.participante_um) || 
    !strcmp(a.participante_um, b.participante_dois) || !strcmp(a.participante_um, b.participante_tres)){
        if(a.dia == b.dia && a.inicio < duracaoParaHora(b)){
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_um);
            teste = 0;
        }
    }
    
    if (a.numParticipantes == 3){
        if(!strcmp(a.participante_tres, b.participante_dois) || !strcmp(a.participante_tres, b.participante_tres)|| 
        !strcmp(a.participante_tres, b.participante_um) || !strcmp(a.participante_tres, b.responsavel)){
            if(a.dia == b.dia && a.inicio < duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_tres);
                teste = 0;
            }
        }
           

        if(!strcmp(a.participante_dois, b.participante_dois) || !strcmp(a.participante_dois, b.participante_tres) ||
        !strcmp(a.participante_dois, b.participante_um) || !strcmp(a.participante_dois, b.responsavel)){
            if(a.dia == b.dia && a.inicio < duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_dois);
                teste = 0;
            }
        }
    }

    if(a.numParticipantes == 2){
        if(!strcmp(a.participante_dois, b.participante_dois) || !strcmp(a.participante_dois, b.participante_tres)|| 
        !strcmp(a.participante_dois, b.participante_um) || !strcmp(a.participante_dois, b.responsavel)){
            if(a.dia == b.dia && a.inicio < duracaoParaHora(b)){
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participante_dois);
                teste = 0;
            }
        }
    }
    return teste;
}

int ordenaData(evento a){
    int ano = (a.dia%10000);
    int mes = ((a.dia%1000000) - ano)/100;
    int dia = a.dia/1000000;
    return (ano*10000 + mes + dia)*10000 + a.inicio;
    
}

void ordenaEventos(evento reservaSalas[SALAS*EVENTOS], int numEventos){
    int i, j;
    evento a;
    for (i = 0; i < numEventos; i++){
        for(j = i + 1; j < numEventos; j++){
            if (ordenaData(reservaSalas[i]) > ordenaData(reservaSalas[j])){
                a = reservaSalas[i];
                reservaSalas[i] = reservaSalas[j];
                reservaSalas[j] = a;
            }
        }
    }
}

int procuraDescricao(char descricao[MAXIMO_NOME], evento reservaSalas[SALAS*EVENTOS], int numEventos){
    int indice = -1, i;
    for(i = 0; i < numEventos; i++){
        if(!strcmp(descricao, reservaSalas[i].descricao)){
            indice = i;
        }
    }
    return indice;

}
