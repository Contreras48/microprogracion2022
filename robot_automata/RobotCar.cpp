/*
Libejemplo.cpp -Descripción cpp
Creada por Nombre Autor, Fecha
Lanzado bajo licencia---
*/

#include "Arduino.h"
#include "RobotCar.h"
/* **************************************
**      CLASE ULTRASONIDO
************************************** */
//Constructor parametrizado
Ultrasonido::Ultrasonido(byte &_pinTrigger, byte &_pinEcho){
  pinTrigger=_pinTrigger;
  pinEcho=_pinEcho;
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

//hace la medicion de distancia devuelve cms de distancia hasta 350cm maxi
int Ultrasonido::medir(){
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(4);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  distancia=pulseIn(pinEcho,HIGH)/56.5812;
  distancia=constrain(distancia,0,350);
  return (int) distancia;
}

/*  **************************************************************
                  CLASE CARRO
***********************************************************
*/
//inicializando las variables staticas de la CLASE
volatile unsigned int Carro::contaI = 0;
volatile unsigned int Carro::contaD = 0;

Carro::Carro(){
	pinMode(encoderI,INPUT);
    pinMode(encoderD,INPUT);
    pinMode(adelanteI,OUTPUT);
    pinMode(atrasI,OUTPUT);
    pinMode(potenciaI,OUTPUT);
    pinMode(adelanteD,OUTPUT);
    pinMode(atrasD,OUTPUT);
    pinMode(potenciaD,OUTPUT);

    //instanciando los sensores ultrasonido y refiriendo
    // invoco constructor parametrizado, new devuelve un puntero
    UltraC= new Ultrasonido(sensortrigerC,sensorechoC);
    UltraI= new Ultrasonido(sensortrigerI,sensorechoI);
    UltraD= new Ultrasonido(sensortrigerD,sensorechoD);

    //UltraD->medir(); //para acceder a sus miembros uso -> por ser puntero

    //ALTERNATIVO PODRIA SER  
    //UltraD=*(new Ultrasonido(sensortrigerD,sensorechoD)); //instan como objeto uso * para referenciar
    //Ultra.medir() //accedo a sus miembros como objeto
    //UltraD=*(new Ultrasonido(sensortrigerD,sensorechoD)); //si es alias uso * para referenciar
    //Ultra.medir() //accedo a sus miembros como objeto por ser un alias


	//Agregamos este codigo para registrar las interrupciones
    //RISING indica que se disparara la interrupcion cuando el pin cambie de 0 a 1
    attachInterrupt(digitalPinToInterrupt(encoderI), Carro::contarRuedaI,RISING);
    attachInterrupt(digitalPinToInterrupt(encoderD), Carro::contarRuedaD,RISING);
	  Carro::contaI=0; //contadores a cero
    Carro::contaD=0;
}

//METODOS QUE SE EJECUTAN CON LA INTERRUPCION
//Son metodos Staticos pero static va en el .H
void Carro::contarRuedaI(){
    //Carro::contaI = Carro::contaI >= 65000 ? 1 : Carro::contaI++;

    if (Carro::contaI < 65000)
        Carro::contaI++;
    else
        Carro::contaI = 1;
    
    //Serial.println(Carro::contaI);
}
void Carro::contarRuedaD(){
    //Carro::contaD = Carro::contaD >= 65000 ? 1 : Carro::contaD++;

    if (Carro::contaD < 65000)
        Carro::contaD++;
    else
        Carro::contaD = 1;
    
    //Serial.println(Carro::contaD);
}

//metodo para mover el carro + adelante, - atras, potencia abs
void Carro::mover(int izquierda, int derecha){
  izquierda = constrain(izquierda, -10, 10);
  derecha = constrain(derecha, -10, 10);
  
  //Rueda Izquierda
    if (izquierda<0){
        digitalWrite(adelanteI,LOW);
        digitalWrite(atrasI,HIGH);
    }
    else if(izquierda>0){
        digitalWrite(adelanteI,HIGH);
        digitalWrite(atrasI,LOW);
    }else {
        digitalWrite(adelanteI,LOW);
        digitalWrite(atrasI,LOW);
    }
    
    // RUEDA DERECHA
    if (derecha<0){
        digitalWrite(adelanteD,LOW);
        digitalWrite(atrasD,HIGH);
    }
    else if(derecha>0){
        digitalWrite(adelanteD,HIGH);
        digitalWrite(atrasD,LOW);
    }else {
        digitalWrite(adelanteD,LOW);
        digitalWrite(atrasD,LOW);
    }
	
  
  //Potencia indicada en pines PWN
  //AJUSTANDO LA POTENCIA
  // si tienes contadores de vuelta aquí agregarás el ajuste para que avance recto

    derecha=abs(derecha);
    izquierda=abs(izquierda);

    if(contaI > contaD){
      izquierda=map(izquierda,0,10,0,potenciaMAX-20);   
      derecha=map(derecha,0,10,0,potenciaMAX);
    }else if(contaI < contaD){
      izquierda=map(izquierda,0,10,0,potenciaMAX);   
      derecha=map(derecha,0,10,0,potenciaMAX-20);
    }else{
      izquierda=map(izquierda,0,10,0,potenciaMAX);   
      derecha=map(derecha,0,10,0,potenciaMAX);
    }
    
//    izquierda=map(izquierda,0,10,0,potenciaMAX);   
//    derecha=map(derecha,0,10,0,potenciaMAX);
    analogWrite(potenciaD,derecha);
    analogWrite(potenciaI,izquierda);
}

//Gira la cantidad de grados especifica: - a la izquierda, + derecha
//usa los contadores de vuelta para la precision al girar
//tu decides si usas dos llantas para girar o solo una
//Si tienes contadores de rueda los usaras para hacer el giro
//si no tienes contadores haras un aproximado con delay(tiempo)

void Carro::girar(int grados){
    float medioGiro=40;
    int parar=grados*(medioGiro/180);
    parar=abs(parar);
    mover(0,0);
    delay(100);
    contaI=0;
    contaD=0;
    if(grados>0){
        mover(10,-10); //girando moviendo las dos llantas 
    }else if(grados<0){
        mover(-10,10); 
    }
    while(contaI + contaD < parar){
      Serial.print("contadore: ");
        Serial.println(contaD+contaI);
        Serial.print("Parar: ");
        Serial.println(parar);
    }
    mover(0,0);
    delay(100);
}
