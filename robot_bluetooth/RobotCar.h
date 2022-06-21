/*
  Libreria de RobotCar
Universidad de El Salvador, Sede Santa Ana
ciclo I-2019 
*/
#ifndef RobotCar_h
#define RobotCar_h
#include "Arduino.h"


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
	byte potenciaMAX=255;
	
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
