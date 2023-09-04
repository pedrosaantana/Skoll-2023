#include "motores/motor.h"

#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H

typedef struct{
    int esq;
    int fesq;
    //int cen_esq;
    int cen;
    //int cen_dir;
    int fdir;
    int dir;
}Distancia; 

typedef struct{
    int esq;
    int dir;
    int t_esq;
    int t_dir;
}Linha;

typedef struct{
    int esq;
    int dir;
}Corrente;

// void moverMotor(char lado, char direcao, int vel);
// void pararMotor()
// Ambas já existem!

bool getStart();

Distancia getDistancia();

Linha getLinha();

Corrente getCorrente();

bool verLinha(Linha lin);

double getInimigo(Distancia dist);

#endif