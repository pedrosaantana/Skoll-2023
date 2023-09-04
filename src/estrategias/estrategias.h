#include <Arduino.h>
#include "sensores/sensores.h"
#include "motores/motor.h"
#include "funcoes_basicas/funcoes_basicas.h"

#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

#define PARAR_CMD 0
#define LED_CMD 1
#define PWM_CMD 2
#define M_FRENTE_CMD 3
#define M_TRAS_CMD 4
#define PARAR_LINHA_CMD 5
#define GIRAR_NO_EIXO_CMD 6
#define GIRAR_EM_CIRC_CMD 7
#define REPOSICIONAR_CMD 8
#define ALINHAR_CMD 9
#define TESTE_DIST_CMD 10
#define TESTE_LINHA_CMD 11
#define TESTE_PROTO 12

// Funções de teste
void piscarLed();

void testePWM();

void testeMotorFrente(int vel);

void testeMotorTras(int vel);

void girarNoEixo(int vel);

void girarEmCirculos(int vel, int correcao);

void testeLinha(int vel);

void alinharRobo(int vel);

// ESTRATÉGIAS

void missel_1();  // com dist

void missel_2();  // sem dist

void strat_busca();

void basica();

void testeCorrecao(int vel);

#endif