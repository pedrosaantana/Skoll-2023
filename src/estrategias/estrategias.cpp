#include "estrategias/estrategias.h"

// PARAMETROS

int tempo180 = 200;
int tempo90 = (tempo180/2);
int tempoBusca = 1.5*tempo180;

/*
    DECLARAÇÃO DOS TIMERS
*/

hw_timer_t * timer;

void iniciarTimer(){
  timer = timerBegin(0, 80, true);
  timerAlarmWrite(timer, 0, true);
  timerAlarmEnable(timer);
}

void resetaTimer(){
  timerAlarmWrite(timer, 0, true);
}

void pararTimer(){
  timerEnd(timer);
  timer = NULL;
}

unsigned long long obterTimer(){
  return timerReadMilis(timer);
}

/*
    FUNÇÕES DE TESTES BASICOS
*/

void piscarLed(){
    gpio_set_level(LED, HIGH);
    delay(1000);
    gpio_set_level(LED, LOW);
    delay(1000);
}

void testePWM(){
    pwmASetDuty(10);
    pwmBSetDuty(40);
    pwmCSetDuty(70);
    pwmDSetDuty(100);
}

void testeCorrecao(int vel){
    moverMotor('e', 'f', 50);
    moverMotor('d', 'f', vel);
}

void testeMotorFrente(int vel){
    moverMotor('e', 'f', vel);
    moverMotor('d', 'f', vel);
}

void testeMotorTras(int vel){
    moverMotor('e', 't', vel);
    moverMotor('d', 't', vel);
}

void girarNoEixo(int vel){

    // Sentido horário
    moverMotor('e', 'f', vel);
    moverMotor('d', 't', vel);
}

void girarEmCirculos(int vel, int correcao){
    moverMotor('e', 'f', vel);
    moverMotor('d', 'f', vel-correcao);
}

void alinharRobo(int vel){
    double pos = getInimigo(getDistancia());

    if(pos < 3.0){
        moverMotor('e', 'f', 60);
        moverMotor('d', 'f', 70);
    }

    if(pos > 3.0){
        moverMotor('e', 'f', 70);
        moverMotor('d', 'f', 60);
    }

    if(pos == 3.0){
        moverMotor('e', 'f', 100);
        moverMotor('d', 'f', 100);
    }
}

void testeLinha(int vel){   // mais simples, apenas para teste,m mas não cobre os problemas de verificação do inimigo
    if(verLinha(getLinha())){
        moverMotor('e', 't', 90);
        moverMotor('d', 't', 90);
        delay(100);
        girarNoEixo(70);
        delay(200);
        pararMotor();
    }
    else{
        testeMotorFrente(vel);
    }
}

/*
    ESTRATEGIAS
*/

void missel_1(){   // Missel utilizando os sensores de distancia
    double pos = getInimigo(getDistancia());

    if(verLinha(getLinha())){
        moverMotor('e', 't', 90);
        moverMotor('d', 't', 90);
        delay(100);
        girarNoEixo(70);
        delay(200);
        pararMotor();
    } else{
        if(pos < 3.0 && pos > 0.0){
            moverMotor('e', 't', 70);
            moverMotor('d', 'f', 70);
        }
        if(pos > 3.0 && pos > 0.0){
            moverMotor('e', 'f', 70);
            moverMotor('d', 't', 70);
        }
        if(pos == 3.0){
            moverMotor('e', 'f', 100);
            moverMotor('d', 'f', 100);
        }
    }

    
}

void missel_2(){  // Míssel sem sensores de distancia
   
    if(verLinha(getLinha())){
        moverMotor('e', 't', 90);
        moverMotor('d', 't', 90);
        delay(100);
        girarNoEixo(70);
        delay(200);
        pararMotor();
    } else{
        moverMotor('e', 'f', 100);
        moverMotor('d', 'f', 100);
    }
}

void strat_busca(){
    double pos = getInimigo(getDistancia());

    if(verLinha(getLinha())){
        moverMotor('e', 't', 90);
        moverMotor('d', 't', 90);
        delay(150);
        moverMotor('e', 'f', 70);
        moverMotor('d', 't', 70);
        delay(200);
    }
    else 
    if(getInimigo(getDistancia()) == (0.0) ){ // && !verLinha(getLinha())
            for(int i = 0; i < 10; i++){
                if(getInimigo(getDistancia()) > (0.0) || !getStart()) break;
                moverMotor('e', 'f', 60);
                moverMotor('d', 'f', 70);
                delay(10);
            }

            for(int i = 0; i < 10; i++){
                if(getInimigo(getDistancia()) > (0.0) || !getStart()) break;
                moverMotor('e', 'f', 70);
                moverMotor('d', 't', 70);
                delay(10);
            }
    }else{
        pos = getInimigo(getDistancia());

        if(pos < 3.0){
            moverMotor('e', 'f', 60);
            moverMotor('d', 'f', 70);
        }

        if(pos > 3.0){
            moverMotor('e', 'f', 70);
            moverMotor('d', 'f', 60);
        }

        if(pos == 3.0){
            moverMotor('e', 'f', 100);
            moverMotor('d', 'f', 100);
        }
    }
} 

void basica(){
    if(verLinha(getLinha())){
        moverMotor('e', 't', 90);
        moverMotor('d', 't', 90);
        delay(150);
        moverMotor('e', 'f', 70);
        moverMotor('d', 't', 70);
        delay(200);
    }
    else{
        double pos = getInimigo(getDistancia());

        if(pos < 3.0 && pos > 0.0){
            moverMotor('e', 'f', 60);
            moverMotor('d', 'f', 70);
        }

        if(pos > 3.0){
            moverMotor('e', 'f', 80);
            moverMotor('d', 'f', 60);
        }

        if(pos == 3.0){
            moverMotor('e', 'f', 100);
            moverMotor('d', 'f', 100);
        }

        if(pos == 0.0){
            pararMotor();
        }
    }
}