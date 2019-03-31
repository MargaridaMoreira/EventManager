#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALAS 10
#define EVENTOS 100
#define MAXIMO_NOME 64
#define MAX 1024

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

int ordena = 1;

void adicionaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos);
void listaSala(int sala, evento reservaSalas[SALAS*EVENTOS], int numEventos);
void listaEvento(evento reservaSalas[SALAS*EVENTOS],int numEventos);
void apagaEvento(evento reservaSalas[SALAS*EVENTOS], int *numEventos);
void alteraInicio(evento reservaSalas[EVENTOS*SALAS], int numEventos);
void alteraDuracao(evento reservaSalas[EVENTOS*SALAS], int numEventos);
void alteraSala(evento reservaSalas[EVENTOS*SALAS], int numEventos);
void adicionaParticipante(evento reservaSalas[EVENTOS*SALAS], int numEventos);
void removeParticipante(evento reservaSalas[EVENTOS*SALAS], int numEventos);
int horaFinal(evento a);
int verifica(evento a, evento existente);
int verificaParticipante(char participante[MAXIMO_NOME], evento a, evento b);
int verificaP(char participante[MAXIMO_NOME], evento a, evento b);
int ordenaData(evento a);
void ordenaEventos(evento reservaSalas[SALAS*EVENTOS], int numEventos);
int cmpfunc (const void * evento1, const void * evento2);
int procuraDescricao(char descricao[MAXIMO_NOME], evento reservaSalas[SALAS*EVENTOS], int numEventos);

int main(){
    evento reservaSalas[SALAS * EVENTOS] = {0};
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
            case 't':
                    getchar();
                    alteraDuracao(reservaSalas, numEventos);
                    break;
            case 'm':
                    getchar();
                    alteraSala(reservaSalas, numEventos);
                    break;
            case 'A':
                    getchar();
                    adicionaParticipante(reservaSalas, numEventos);
                    break;
            case 'R':
                    getchar();
                    removeParticipante(reservaSalas, numEventos);
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
        if(a.sala == reservaSalas[i].sala && !verifica(a, reservaSalas[i])){
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            return;
        }
    }

    for(i = 0; i < (*numEventos); i ++){
        if(!verificaParticipante(a.responsavel, reservaSalas[i], a)){
            teste = 0;
        }
        if(!verificaParticipante(a.participante_um, reservaSalas[i], a)){
            teste = 0;
        }
        if(a.numParticipantes == 3){
            if(!verificaParticipante(a.participante_dois, reservaSalas[i], a)){
                teste = 0;
            }
            if(!verificaParticipante(a.participante_tres, reservaSalas[i], a)){
                teste = 0;
            }
        }
        if(a.numParticipantes == 2){
            if(!verificaParticipante(a.participante_dois, reservaSalas[i], a)){
                teste = 0;
            }
        }  
    }
   
    if(teste){
        reservaSalas[(*numEventos)] = a;
        (*numEventos) ++;
        ordena = 0;
    }
    return;
}

void listaSala(int sala, evento reservaSalas[SALAS*EVENTOS],int numEventos){
    int i;
    if(!ordena){
        ordenaEventos(reservaSalas, numEventos);
    }
    for(i = 0; i < numEventos; i ++){
        if(reservaSalas[i].sala == sala){
            printf("%s %08d %04d %d Sala%d %s\n", reservaSalas[i].descricao, reservaSalas[i].dia, 
                   reservaSalas[i].inicio, reservaSalas[i].duracao, reservaSalas[i].sala, reservaSalas[i].responsavel);
            if(reservaSalas[i].numParticipantes == 3){
                printf("* %s %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois, 
                   reservaSalas[i].participante_tres);
            } else if (reservaSalas[i].numParticipantes == 2){
                printf("* %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois);
            } else {
                printf("* %s\n", reservaSalas[i].participante_um);
            }  
        }
    }
    return;  
}

void listaEvento(evento reservaSalas[SALAS*EVENTOS],int numEventos){
    int i;
    if(!ordena){
        ordenaEventos(reservaSalas, numEventos);
    }
    for(i = 0; i < numEventos; i ++){
        printf("%s %08d %04d %d Sala%d %s\n", reservaSalas[i].descricao, reservaSalas[i].dia, 
               reservaSalas[i].inicio, reservaSalas[i].duracao, reservaSalas[i].sala, reservaSalas[i].responsavel);
        if(reservaSalas[i].numParticipantes == 3){
                printf("* %s %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois, 
                reservaSalas[i].participante_tres);
        } else if (reservaSalas[i].numParticipantes == 2){
            printf("* %s %s\n", reservaSalas[i].participante_um, reservaSalas[i].participante_dois);
        } else {
            printf("* %s\n", reservaSalas[i].participante_um);
        }    
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
    } else if (indice == (EVENTOS * SALAS)-1) {
        (*numEventos)--;
    } else {
        for(i = indice; i < ((*numEventos)-1); i++){
            reservaSalas[i] = reservaSalas[i + 1];
        }
        (*numEventos)--;


        /*memmove(&reservaSalas[indice], &reservaSalas[indice + 1], ((*numEventos)) * sizeof(reservaSalas[indice]));*/
        
    }
    return;

}

void alteraInicio(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c, indice, teste = 1;
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

    indice = procuraDescricao(descricao[0], reservaSalas, numEventos);
    
    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        a = reservaSalas[indice];
        a.inicio = atoi(descricao[1]);
        for(i = 0; i < numEventos; i ++){
            if (indice != i){
                if(a.sala == reservaSalas[i].sala){
                    if(!verifica(a, reservaSalas[i])){
                        printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
                        return;
                    }
                }
                if(!verificaParticipante(a.responsavel, reservaSalas[i], a)){
                    teste = 0;
                }
                if(!verificaParticipante(a.participante_um, reservaSalas[i], a)){
                    teste = 0;
                }
                if(a.numParticipantes == 3){
                    if(!verificaParticipante(a.participante_dois, reservaSalas[i], a)){
                        teste = 0;
                    }
                    if(!verificaParticipante(a.participante_tres, reservaSalas[i], a)){
                        teste = 0;
                    }  
                }
                if(a.numParticipantes == 2){
                    if(!verificaParticipante(a.participante_dois, reservaSalas[i], a)){
                        teste = 0;
                    }
                }
                       
            }
        }
        if(teste){
            ordena = 0;
            reservaSalas[indice].inicio = atoi(descricao[1]);
        }
    }
    return;
}

void alteraDuracao(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c, indice, teste = 1;
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
    
    indice = procuraDescricao(descricao[0], reservaSalas, numEventos);
    
    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        a = reservaSalas[indice];
        a.duracao = atoi(descricao[1]);
        for(i = 0; i < numEventos; i ++){
            if (indice != i){
                if(a.sala == reservaSalas[i].sala){
                    if(!verifica(a, reservaSalas[i])){
                        printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
                        return;
                    }
                }
                if(!verificaParticipante(a.responsavel, reservaSalas[i], a)){
                    teste = 0;
                }
                if(!verificaParticipante(a.participante_um, reservaSalas[i], a)){
                    teste = 0;
                }
                if(!verificaParticipante(a.participante_dois, reservaSalas[i], a)){
                    teste = 0;
                }
                if(!verificaParticipante(a.participante_tres, reservaSalas[i], a)){
                    teste = 0;
                }         
            }
        }
        if(teste){
            ordena = 0;
            reservaSalas[indice].duracao = atoi(descricao[1]);
        }
    }
    return;
}

void alteraSala(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c, indice;
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
    
    indice = procuraDescricao(descricao[0], reservaSalas, numEventos);
    
    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        a = reservaSalas[indice];
        a.sala = atoi(descricao[1]);
        for(i = 0; i < numEventos; i ++){
            if (indice != i && a.sala == reservaSalas[i].sala && !verifica(a, reservaSalas[i])){
                printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
                return;                        
            }
        }
        ordena = 0;
        reservaSalas[indice].sala = atoi(descricao[1]);
    }
}

void adicionaParticipante(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c, indice;
    char descricao[2][MAXIMO_NOME] = {0}, texto[MAX], *token;

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
    indice = procuraDescricao(descricao[0], reservaSalas, numEventos);
    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        if(reservaSalas[indice].numParticipantes == 3){
            printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n",descricao[0]);
            return;            
        } else if (!strcmp(descricao[1], reservaSalas[indice].responsavel) || !strcmp(descricao[1], reservaSalas[indice].participante_um) ||
             !strcmp(descricao[1], reservaSalas[indice].participante_dois) || !strcmp(descricao[1], reservaSalas[indice].participante_tres)){
            return;
        }
        for(i = 0; i < numEventos; i ++){
            if(!verificaP(descricao[1], reservaSalas[i], reservaSalas[indice])){
                printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", descricao[1]);
                return;
            }
        
        }
        if(reservaSalas[indice].numParticipantes == 2){
            strcpy(reservaSalas[indice].participante_tres, descricao[1]);
            reservaSalas[indice].numParticipantes ++;
        } 
        if(reservaSalas[indice].numParticipantes == 1) {
            strcpy(reservaSalas[indice].participante_dois, descricao[1]);
            reservaSalas[indice].numParticipantes ++;
        }
    }
}

void removeParticipante(evento reservaSalas[EVENTOS*SALAS], int numEventos){
    int i, c, indice;
    char descricao[2][MAXIMO_NOME] = {0}, texto[MAX], *token;

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
    indice = procuraDescricao(descricao[0], reservaSalas, numEventos);
    
    if(indice == -1){
        printf("Evento %s inexistente.\n", descricao[0]);
        return;
    } else {
        if(strcmp(descricao[1], reservaSalas[indice].participante_um) && strcmp(descricao[1], reservaSalas[indice].participante_dois) 
        && strcmp(descricao[1], reservaSalas[indice].participante_tres)){
            return;
        } else if(reservaSalas[indice].numParticipantes == 1){
            printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", descricao[1], descricao[0]);
        } else if (reservaSalas[indice].numParticipantes == 2){
            if(!strcmp(descricao[1], reservaSalas[indice].participante_um)){
                strcpy(reservaSalas[indice].participante_um,reservaSalas[indice].participante_dois);
                reservaSalas[indice].participante_dois[0] = '\0'; 
                reservaSalas[indice].participante_tres[0] = '\0';                               
                reservaSalas[indice].numParticipantes --;
            } else if (!strcmp(descricao[1], reservaSalas[indice].participante_dois)){
                reservaSalas[indice].participante_dois[0] = '\0';
                reservaSalas[indice].participante_tres[0] = '\0';
                reservaSalas[indice].numParticipantes --;
            }
            
        } else if(reservaSalas[indice].numParticipantes == 3){
            if(!strcmp(descricao[1], reservaSalas[indice].participante_um)){
                strcpy(reservaSalas[indice].participante_um,reservaSalas[indice].participante_dois);
                reservaSalas[indice].participante_dois[0] = '\0'; 
                reservaSalas[indice].participante_tres[0] = '\0';                               
                reservaSalas[indice].numParticipantes --;
            } else if (!strcmp(descricao[1], reservaSalas[indice].participante_dois)){
                reservaSalas[indice].participante_dois[0] = '\0';
                reservaSalas[indice].participante_tres[0] = '\0';
                reservaSalas[indice].numParticipantes --;
            } else if (!strcmp(descricao[1], reservaSalas[indice].participante_tres)){
                reservaSalas[indice].participante_tres[0] = '\0';
                reservaSalas[indice].numParticipantes --;
            }
        }
    }
}

int horaFinal(evento a){
    int hora, minutos;
    hora = a.inicio;
    hora = hora + 100*(a.duracao/60) + a.duracao%60;
    minutos = hora%100;
    hora = ((hora/100) + minutos/60) * 100 + (minutos%60);
    return hora;
}

int ordenaData(evento a){
    int ano = (a.dia%10000);
    int mes = ((a.dia%1000000) - ano)/100;
    int dia = a.dia/1000000;
    return (ano*10000 + mes + dia)*10000 + a.inicio;  
}

void ordenaEventos(evento reservaSalas[SALAS*EVENTOS], int numEventos){
    qsort(reservaSalas, numEventos, sizeof(evento), cmpfunc);
}

int cmpfunc (const void * evento1, const void * evento2) {
    if (ordenaData(*(evento*)evento1) == ordenaData(*(evento*)evento2) && (*(evento*)evento1).sala > (*(evento*)evento2).sala){
        return (( *(evento*)evento1).sala - (*(evento*)evento2).sala);
    }
    return (ordenaData(*(evento*)evento1) - ordenaData(*(evento*)evento2));
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

int verifica(evento a, evento existente){
    if(a.dia == existente.dia){
        if (a.inicio > existente.inicio){
            if(horaFinal(existente) > a.inicio){
                return 0;
            } else {
                return 1;
            }
        } else if (a.inicio < existente.inicio){
            if(horaFinal(a) > existente.inicio){
                return 0;
            } else {
                return 1;
            }
        } else if (a.inicio == existente.inicio){
            return 0;
        }
    }
    return 1;
}

int verificaParticipante(char participante[MAXIMO_NOME], evento a, evento b){
    int teste = 1;
    if(!strcmp(participante, a.participante_um) || !strcmp(participante, a.participante_dois) || 
       !strcmp(participante, a.responsavel) || !strcmp(participante, a.participante_tres)){
            if(!verifica(b, a)){
                teste = 0;
                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", b.descricao, participante);
            } 
    } 
    return teste;  
}

int verificaP(char participante[MAXIMO_NOME], evento a, evento b){
    int teste = 1;
    if(!strcmp(participante, a.participante_um) || !strcmp(participante, a.participante_dois) || 
       !strcmp(participante, a.responsavel) || !strcmp(participante, a.participante_tres)){
            if(!verifica(b, a)){
                teste = 0;
            } 
    } 
    return teste;  
}