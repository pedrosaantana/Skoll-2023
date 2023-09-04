#include "funcoes_basicas/funcoes_basicas.h"

int parametro_linha = 1100;
int parametro_corrente = 2887;
// analog de 12 bits
// ajustar os valores corretamente!


bool getStart(){
    return gpio_get_level(START);
}

Distancia getDistancia(){   // INVERTER PRA TESTAR O ROBO
    Distancia dist;

    dist.esq = !gpio_get_level(SENSOR_DIST_ESQ);
    dist.fesq = !gpio_get_level(SENSOR_DIST_FRONTAL_ESQ);
    dist.cen = !gpio_get_level(SENSOR_DIST_CENTRAL);
    dist.fdir = !gpio_get_level(SENSOR_DIST_FRONTAL_DIR);
    dist.dir = !gpio_get_level(SENSOR_DIST_DIR);

    return dist;
}

Linha getLinha(){
    Linha lin;

    if(analogRead(SENSOR_LINHA_FRONTAL_ESQ) < parametro_linha ){
        lin.esq = 1;
    }
    else{
        lin.esq = 0;
    }
    if(analogRead(SENSOR_LINHA_FRONTAL_DIR) < parametro_linha ){
        lin.dir = 1;
    }
    else{
        lin.dir = 0;
    }
    if(analogRead(SENSOR_LINHA_TRASEIRO_ESQ) < parametro_linha ){
        lin.t_esq = 1;
    }
    else{
        lin.t_esq = 0;
    }
    if(analogRead(SENSOR_LINHA_TRASEIRO_DIR) < parametro_linha ){
        lin.t_dir = 1;
    }
    else{
        lin.t_dir = 0;
    }

    return lin;
}

Corrente getCorrente(){
    Corrente corr;

    if(analogRead(SENSOR_CORRENTE_DIR) > parametro_corrente ){
        corr.dir = 1;
    }
    else{
        corr.dir = 0;
    }
    if(analogRead(SENSOR_CORRENTE_ESQ) > parametro_corrente ){
        corr.esq = 1;
    }
    else{
        corr.esq = 0;
    }

    return corr;
}

bool verLinha(Linha lin){
    if(lin.dir /*|| lin.esq*/){
        return true;
    }
    else{
        return false;
    }
}

double getInimigo(Distancia dist){
    double pos = 0.0;
    int num_sensores = 0;
    /*
    1 - Esquerdo
    2 - Frontal Esquerdo
    3 - Central
    4 - Frontal Direito
    5 - Direito
    */
   
    if(dist.esq){
        pos += 1;
        num_sensores++;
    }
    if(dist.fesq){
        pos += 2;
        num_sensores++;
    }
    if(dist.cen){
        pos += 3;
        num_sensores++;
    }
    if(dist.fdir){
        pos += 4;
        num_sensores++;
    }
    if(dist.dir){
        pos += 5;
        num_sensores++;
    }

    if(num_sensores > 0)
    {
        return pos/num_sensores;
    }
    return 0.0;
   
}