/*
  Libreria de RobotCar
Universidad de El Salvador, Sede Santa Ana
ciclo I-2019 
*/
#ifndef RobotCar_h
#define RobotCar_h
#include "Arduino.h"

//Representa un sensor de ultrasonido al construir el objeto
//se pasan los pines de Trigger y Echo 
class Ultrasonido{
    public:
		int pinEcho;
   	int pinTrigger;
   	long distancia;
	//Constructor parametrizado Recibe como parametros Trigger y Echo como byte
  Ultrasonido(byte &_pinTrigger, byte &_pinEcho);
      

   //Mide la distancia el sensor es preciso hasta 3.5mts
   // por tanto el valor maximo es 350 cms
   int medir();  
};

//******************C L A S E   C A R R O **************************
class Carro{
	public:
	byte encoderI=2;  //pin del encoder de la llanta izquierda
	byte encoderD=3;  // pin del encoder de la llanta derecha
	byte adelanteI=4; // pin avance adelante llanta Izquierda
	byte atrasI=5;    // pin de reversa llanta izquierda
	byte potenciaI=6; // pin de potencia llanta Izquierda pin PWM
	byte adelanteD=7; // Adelante llanta Derecha
	byte atrasD=8;  // atras llanta Derecha
	byte potenciaD=9;  // potencia llanta Derecha pin PWM
	byte sensortrigerC=10; //Sensor Ultrasonido Central Trigger
	byte sensorechoC=11; //Sensor Ultrasonido Central Echo
	byte sensortrigerI=12; //Sensor Ultrasonido Izquierda Trigger
	byte sensorechoI=13; //Sensor Ultrasonido Izquierda Echo
	byte sensortrigerD=14; //Sensor Ultrasonido Derecha Trigger
	byte sensorechoD=15; //Sensor Ultrasonido Derecha Echo
	byte potenciaMAX=200;
	
	Ultrasonido *UltraC; // Se declara como puntero
	Ultrasonido *UltraI; // en el cpp se va a instanciar y a referir
	Ultrasonido *UltraD;
	//Ultrasonido UltraC  //forma alternativa como objeto
	//Ultrasonido &UltraC  //forma alternativa como alias	
	
	//DEFINIENDO LAS INTERRUPCIONES--USAN MIEMBROS ESTATICOS
	static volatile unsigned int contaI; //contador de las vueltas de la llanta Izquierda
	static volatile unsigned int contaD; //contador de las vueltas de la llanta Derecha
	//CONTADORES DE RUEDAS IZQUIERDA Y DERECHA
	static void contarRuedaI(); //metodo a registrar con la interrupcion en constructor
	static void contarRuedaD();
	
	//Constructor -- configura variables, sensores e interrupciones
	Carro();
	
	//acciona el motor, recibe como parametro la accion en la llanta izquierda y la llanta derecha
	// el valor de cada llanta si es positivo movera la llanta hacia adelante
	// si es negativo movera la llanta hacia atras
	// el numero representara la potencia aplicada a cada llanta
	// los valores pueden ir de -255 hasta 255
	void mover(int Izquierda, int Derecha);
	
	//Gira la cantidad de grados especifica: - a la izquierda, + derecha
	//usa los contadores de vuelta para la precision al girar
	//tu decides si usas dos llantas para girar o solo una
	void girarI(int grados);
	void girarD(int grados);
  void girar(int grados);
	
};


#endif
