#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "estrategias/estrategias.h"
#include "funcoes_basicas/funcoes_basicas.h"
#include "motores/motor.h"
#include "sensores/sensores.h"

#define SERVICE_UUID "f2898d83-25f4-42e0-a3a8-71a2588ff27e"
#define CHARACTERISTIC_UUID "c63a00bc-8ac9-42ab-bbba-1c8a7e68ec4b"
//#define LINHA_UUID "a46c67de-287c-452a-b0c2-921cdbe9e6a5"  // foi retirado para facilitar a leitura no bluetooth
#define DIST_UUID "16661315-0625-44dd-89b8-986eb396ed2d"
#define CORR_UUID "c49b7011-6535-4740-83e4-a0b90b503957"
#define TESTE_UUID "ed790a3c-7eed-45f7-8f81-cdd6d2e118d2"

#define bleRobo "SKOLL"
#define ESP_INTR_FLAG_DEFAULT 0

std::string value;

std::string comando = "base";

int vel = 50;           // VELOCIDADE UTILIZADA NAS FUNÇÕES 
int correcao = 0;      // CORRECAO UTILIZADA PARA ARCOS E GIRAR EM CIRCULO
int velGiro = 40;       // VELOCIDADE DE GIRO AO SE REPOSICIONAR
int velArco = 50;       // VELOCIDADE DO ARCO

int velocidade = 01010101;

bool deviceConnected = false ;
bool oldDeviceConnected = false ;

BLEServer* pServer = NULL;

BLECharacteristic bleDistanciaCharacteristics(DIST_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleDistanciaDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleCorrenteCharacteristics(CORR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleCorrenteDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleTesteCharacteristics(TESTE_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleTesteDescriptor(BLEUUID((uint16_t)0x2902));

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    value = pCharacteristic->getValue();

    if(value == "10" || value == "20" || value == "30" || value == "40" || value == "50" || value == "60" || value == "70" || value == "75" || value == "80" || value == "85" || value == "90" || value == "100"){
      vel = stoi(value);
    } else{
      comando = value;
    }
    // ||
  
  void onRead(BLECharacteristic *pCharacteristic);  // n está sendo usado, so ta declarado pra caso um dia use
  };
};

void IRAM_ATTR start_ISR_handler()
{
  //comando = "P";
  pararMotor();
}

void IRAM_ATTR linha_ISR_handler()
{
  piscarLed();
}

void IRAM_ATTR corr_ISR_handler(){
  Corrente corr = getCorrente();

  while(corr.dir || corr.esq){
    pararMotor();
  }
}

void enviaSensores(){
  Distancia dist = getDistancia();
  std::string sensores = "E:";
  sensores.append(std::to_string(dist.esq));
  sensores.append(" FE:");
  sensores.append(std::to_string(dist.fesq));
  sensores.append(" C:");
  sensores.append(std::to_string(dist.cen));
  sensores.append(" FD:");
  sensores.append(std::to_string(dist.fdir));
  sensores.append(" D: ");
  sensores.append(std::to_string(dist.dir));
  sensores.append("      LESQ:");
  sensores.append(std::to_string(analogRead(SENSOR_LINHA_FRONTAL_ESQ)));
  sensores.append(" LDIR:");
  sensores.append(std::to_string(analogRead(SENSOR_LINHA_FRONTAL_DIR)));
  bleDistanciaCharacteristics.setValue(sensores);
  bleDistanciaCharacteristics.notify();
  delay(100);
}

void enviaCorrente(){
  std::string sensores = "CESQ:";
  sensores.append(std::to_string(analogRead(SENSOR_CORRENTE_ESQ)));
  sensores.append(" CDIR:");
  sensores.append(std::to_string(analogRead(SENSOR_CORRENTE_DIR)));
  bleCorrenteCharacteristics.setValue(sensores);
  bleCorrenteCharacteristics.notify();
  delay(100);
}

void testeProto(){
  std::string teste = "Comando lido: ";
  teste.append(comando);
  teste.append("  START: ");
  teste.append(std::to_string(gpio_get_level(START)));
  teste.append("  VEL:  ");
  teste.append(std::to_string(vel));
  teste.append("  POS: ");
  teste.append(std::to_string(getInimigo(getDistancia())));
 
  bleTesteCharacteristics.setValue(teste);
  bleTesteCharacteristics.notify();
}

void setup()
{
  Serial.begin(9600);
  configGpio();
  configAnalog();
  configPWM();

  pinMode(23, OUTPUT);

  BLEDevice::init(bleRobo);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY);

    pService->addCharacteristic(&bleDistanciaCharacteristics);
    bleDistanciaDescriptor.setValue("bleDist");
    bleDistanciaCharacteristics.addDescriptor(&bleDistanciaDescriptor);

    pService->addCharacteristic(&bleCorrenteCharacteristics);
    bleCorrenteDescriptor.setValue("bleCorr");
    bleCorrenteCharacteristics.addDescriptor(&bleCorrenteDescriptor);

    pService->addCharacteristic(&bleTesteCharacteristics);
    bleTesteDescriptor.setValue("bleTeste");
    bleTesteCharacteristics.addDescriptor(&bleTesteDescriptor);

    pCharacteristic->setCallbacks(new MyCallbacks());

    pCharacteristic->setValue("ENVIAR CMD");
    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pServer->getAdvertising()->start();
    pAdvertising->start();

    attachInterrupt(START, start_ISR_handler, FALLING);  // add a interrupt do modulo start
    // attachInterrupt(LINHA_TESTE, linha_ISR_handler, RISING);
    // attachInterrupt(SENSOR_CORRENTE_DIR, corr_ISR_handler, RISING);
    // attachInterrupt(SENSOR_CORRENTE_ESQ, corr_ISR_handler, RISING);
}

void loop()
{
  if (deviceConnected)
  {
    testeProto();
    enviaSensores();
    enviaCorrente();
    delay(5);
  }

  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);
    pServer->startAdvertising();
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected && !oldDeviceConnected)
  {
    oldDeviceConnected = deviceConnected;
  }
  
  while(!getStart()){
    testeProto();
    pararMotor();
    enviaSensores();
    enviaCorrente();
    delay(5);
  } 

  if(comando == "base"){
    basica();
  }

  if(comando == "m1"){
    missel_1();
  }

  if(comando == "m2"){
    missel_2();
  }

  if(comando == "busca"){
    strat_busca();
  }

  if(comando == "motor"){
    testeCorrecao(vel);
  }

  if(comando == "P" || comando == "p"){
    pararMotor();
  } 

  if(comando == "PWM" || comando == "pwm"){
    testePWM();
  }

  if(comando == "FRENTE" || comando == "frente"){
    testeMotorFrente(vel);
  }

  if(comando == "TRAS" || comando == "tras"){
    testeMotorTras(vel);
  }

  if(comando == "EIXO" || comando == "eixo"){  // SENTIDO HORARIO !!! 
    girarNoEixo(vel);
  }

  if(comando == "CIRC" || comando == "circulo"){
    girarEmCirculos(vel, correcao);
  }

  if(comando == "lin" || comando == "linha"){
    testeLinha(vel);
  }

  if(comando == "ALINHAR" || comando == "alinhar"){
    alinharRobo(vel);
  }
}