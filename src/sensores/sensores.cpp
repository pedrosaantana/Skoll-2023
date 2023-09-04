#include "sensores.h"
#include <esp_idf_version.h>

void configAnalog(){
    analogReadResolution(12); // Resolução de 12 bits para leituras analogicas (0 - 4095)
    analogSetWidth(12);
    analogSetAttenuation(ADC_11db);
    adcAttachPin(SENSOR_LINHA_FRONTAL_ESQ);
    adcAttachPin(SENSOR_LINHA_FRONTAL_DIR);
    adcAttachPin(SENSOR_LINHA_TRASEIRO_ESQ);
    adcAttachPin(SENSOR_LINHA_TRASEIRO_DIR);
    adcAttachPin(SENSOR_CORRENTE_DIR);
    adcAttachPin(SENSOR_CORRENTE_ESQ);

    Serial.println("ADC configurado com sucesso!");
}

bool configGpio(){

    // VERIFICAR O PULLUP E PULLDOWN DOS PINOS DOS SENSORES
    // VERIFICAR SE É ATIVO BAIXO OU ALTO (acho que é baixo)
    // VERIFICAR SE OS PINOS TODOS SAO VALIDOS!

    // PINO DE TESTE PARA PROTOBOARD
    gpio_config_t gpio23;   // TESTE
    gpio23.pin_bit_mask = (1ULL << GPIO_NUM_23);
    gpio23.mode = GPIO_MODE_OUTPUT;
    gpio23.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio23.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio23.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio23);

    if(gpio_config(&gpio23) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio22;   // TESTE
    gpio22.pin_bit_mask = (1ULL << GPIO_NUM_22);
    gpio22.mode = GPIO_MODE_INPUT;
    gpio22.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio22.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio22.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio22);

    if(gpio_config(&gpio22) == ESP_ERR_INVALID_ARG){
        return false;
    }

    // SENSORES DE DISTANCIA
    gpio_config_t gpio32;   // SD3 - Sensor lateral esquerdo
    gpio32.pin_bit_mask = (1ULL << GPIO_NUM_32);
    gpio32.mode = GPIO_MODE_INPUT;
    gpio32.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio32.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio32.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio32);

    if(gpio_config(&gpio32) == ESP_ERR_INVALID_ARG){
        return false;
    }
    
    gpio_config_t gpio33;   // SD4 - Sensor frontal esquerdo
    gpio33.pin_bit_mask = (1ULL << GPIO_NUM_33);
    gpio33.mode = GPIO_MODE_INPUT;
    gpio33.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio33.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio33.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio33);

    if(gpio_config(&gpio33) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio25;   // SD5 - Sensor central / Bandeira
    gpio25.pin_bit_mask = (1ULL << GPIO_NUM_25);
    gpio25.mode = GPIO_MODE_INPUT;
    gpio25.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio25.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio25.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio25);

    if(gpio_config(&gpio25) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio26;   // SD6 - Sensor frontal direito
    gpio26.pin_bit_mask = (1ULL << GPIO_NUM_26);
    gpio26.mode = GPIO_MODE_INPUT;
    gpio26.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio26.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio26.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio26);

    if(gpio_config(&gpio26) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio27;   // SD7 - Sensor lateral direito
    gpio27.pin_bit_mask = (1ULL << GPIO_NUM_27);
    gpio27.mode = GPIO_MODE_INPUT;
    gpio27.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio27.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio27.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio27);

    if(gpio_config(&gpio27) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio14;   // SD8 - Sensor central reserva
    gpio14.pin_bit_mask = (1ULL << GPIO_NUM_14);
    gpio14.mode = GPIO_MODE_INPUT;
    gpio14.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio14.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio14.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio14);

    if(gpio_config(&gpio14) == ESP_ERR_INVALID_ARG){
        return false;
    }

    // SENSORES DE LINHA

    gpio_config_t gpio36;   // SL1 - Sensor frontal esquerdo
    gpio36.pin_bit_mask = (1ULL << GPIO_NUM_36); 
    gpio36.mode = GPIO_MODE_INPUT;
    gpio36.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio36.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio36.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio36);

    if(gpio_config(&gpio36) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio39;   // SL2 - Sensor frontal direito
    gpio39.pin_bit_mask = (1ULL << GPIO_NUM_39);
    gpio39.mode = GPIO_MODE_INPUT;
    gpio39.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio39.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio39.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio39);

    if(gpio_config(&gpio39) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio12;   // SL3 - Sensor traseiro esquerdo
    gpio12.pin_bit_mask = (1ULL << GPIO_NUM_12);
    gpio12.mode = GPIO_MODE_INPUT;
    gpio12.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio12.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio12.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio12);

    if(gpio_config(&gpio12) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio13;   // SL4 - Sensor traseiro direito
    gpio13.pin_bit_mask = (1ULL << GPIO_NUM_13);
    gpio13.mode = GPIO_MODE_INPUT;
    gpio13.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio13.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio13.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio13);

    if(gpio_config(&gpio13) == ESP_ERR_INVALID_ARG){
        return false;
    }

    // SENSORES DE CORRENTE

    gpio_config_t gpio4;   // IS-R  - Sensor de corrente direito
    gpio4.pin_bit_mask = (1ULL << GPIO_NUM_4);
    gpio4.mode = GPIO_MODE_INPUT;
    gpio4.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio4.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio4.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio4);

    if(gpio_config(&gpio4) == ESP_ERR_INVALID_ARG){
        return false;
    }

    gpio_config_t gpio2;   // IS-L  - Sensor de corrente esquerdo
    gpio2.pin_bit_mask = (1ULL << GPIO_NUM_2);
    gpio2.mode = GPIO_MODE_INPUT;
    gpio2.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio2.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio2.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio2);

    if(gpio_config(&gpio2) == ESP_ERR_INVALID_ARG){
        return false;
    }

    // Modulo Start

    gpio_config_t gpio15;   // MS - Modulo Start
    gpio15.pin_bit_mask = (1ULL << GPIO_NUM_15);
    gpio15.mode = GPIO_MODE_INPUT;
    gpio15.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio15.pull_down_en = GPIO_PULLDOWN_ENABLE;
    //gpio_intr_enable(START);
    gpio15.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio15);

    if(gpio_config(&gpio15) == ESP_ERR_INVALID_ARG){
        return false;
    }

    Serial.println("GPIO condigurados com sucesso!");
    return true;

}