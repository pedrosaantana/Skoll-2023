#include <Arduino.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef SENSORES_H
#define SENSORES_H

#define SENSOR_CORRENTE_DIR GPIO_NUM_4  // Ver com a eletronica a corrente maxima de acordo com o resistor
#define SENSOR_CORRENTE_ESQ GPIO_NUM_2

/*
#define SENSOR_DIST_ESQ GPIO_NUM_34          // SD1  // n tem pullup
#define SENSOR_DIST_FRONTAL_ESQ GPIO_NUM_35  // SD2  // n tem pullup
#define SENSOR_DIST_CENTRAL_ESQ GPIO_NUM_32  // SD3  
#define SENSOR_DIST_CENTRAL GPIO_NUM_33      // SD4
#define SENSOR_DIST_CENTRAL_DIR GPIO_NUM_25  // SD5 e BANDEIRA
#define SENSOR_DIST_FRONTAL_DIR GPIO_NUM_26  // SD6
#define SENSOR_DIST_DIR GPIO_NUM_27          // SD7
#define SENSOR_DIST_CENTRAL2 GPIO_NUM_14     // SD8 -> reserva pra caso use a bandeira no SD5 (?)
*/

#define SENSOR_DIST_ESQ GPIO_NUM_32          // SD3  
#define SENSOR_DIST_FRONTAL_ESQ GPIO_NUM_33  // SD4
#define SENSOR_DIST_CENTRAL GPIO_NUM_25      // SD5 e BANDEIRA
#define SENSOR_DIST_FRONTAL_DIR GPIO_NUM_26  // SD6
#define SENSOR_DIST_DIR GPIO_NUM_27          // SD7
#define SENSOR_DIST_CENTRAL2 GPIO_NUM_14     // SD8 -> reserva pra caso use a bandeira no SD5 (?)

//CERTO
#define SENSOR_LINHA_TRASEIRO_ESQ GPIO_NUM_36  // SL1
#define SENSOR_LINHA_TRASEIRO_DIR GPIO_NUM_13  // SL4
#define SENSOR_LINHA_FRONTAL_ESQ GPIO_NUM_12 // SL3
#define SENSOR_LINHA_FRONTAL_DIR GPIO_NUM_39 // SL2

// // APENAS PARA TESTE
// #define SENSOR_LINHA_FRONTAL_ESQ GPIO_NUM_12  // SL1
// #define SENSOR_LINHA_FRONTAL_DIR GPIO_NUM_13  // SL2
// #define SENSOR_LINHA_TRASEIRO_ESQ GPIO_NUM_36 // SL3
// #define SENSOR_LINHA_TRASEIRO_DIR GPIO_NUM_39 // SL4

#define START GPIO_NUM_15

// Usados para testes na protoboard
#define LED GPIO_NUM_23
#define LINHA_TESTE GPIO_NUM_22

void configAnalog();
bool configGpio();

#endif

#ifdef __cplusplus
}
#endif