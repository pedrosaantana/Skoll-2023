#include <Arduino.h>
#include "sensores/sensores.h"
#include "pwm/pwm.h"

#ifndef MOTOR_H
#define MOTOR_H

void moverMotor(char lado, char direcao, int vel);

void pararMotor();

#endif