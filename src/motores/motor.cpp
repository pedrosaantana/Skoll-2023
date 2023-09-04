#include "motores/motor.h"

void moverMotor(char lado, char direcao, int vel)
{
    if(lado == 'd'){
        if(direcao == 't'){
            pwmCSetDuty(vel);
            pwmDSetDuty(0);
        }

        if(direcao == 'f'){
            pwmCSetDuty(0);
            pwmDSetDuty(vel);
        }
    }

    if(lado == 'e'){
        if(direcao == 't'){
            pwmASetDuty(vel);  // valores de 0 a 100%
            pwmBSetDuty(0);
        }

        if(direcao == 'f'){
            pwmASetDuty(0);  // valores de 0 a 100%
            pwmBSetDuty(vel);
        }
    }
}

void pararMotor() 
{
    pwmASetDuty(0);  // valores de 0 a 100%
    pwmBSetDuty(0);
    pwmCSetDuty(0);
    pwmDSetDuty(0);
 }