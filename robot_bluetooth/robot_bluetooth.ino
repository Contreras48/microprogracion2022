#include "RobotCar.h"
#include "SoftwareSerial.h"
Carro car;
String DatoBT;
char boton;
SoftwareSerial mySerial(10,11);

 
void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("Conectando");
  
  while(!Serial){
    Serial.print(".");
  }

  Serial.println("Conectado");
  mySerial.println("Listo!!");
  
  
}
 
void loop(){
  BTfuncion();
}

void BTfuncion (){
  if (mySerial.available()>0){
           DatoBT= mySerial.readStringUntil('#');
           Driver();
           Serial.println(DatoBT);
     } 
           
  if (Serial.available()){
        mySerial.write(Serial.read());
  }
}

void Driver(){
  
  String grados = DatoBT.substring(0,3);
  int potencia = DatoBT.substring(3,6).toInt();
  boton = DatoBT.charAt(6); 
  Serial.println(grados);
  Serial.println(boton);


  switch (boton){
    case '4':  // LEFT
      car.mover(-10,10);
      delay(70);
     break;
    case '1':   // UP
      car.mover(10,10); 
      delay(70);
     break;  
    case '2':  // RIGHT
      car.mover(10,-10);     
      delay(70);
     break;   
    case '3':  // dowm
      car.mover(-10,-10);
      delay(70);
     break;   
     case '0': 
      int GradoJoystick = grados.toInt();
      //int PotMotor = potencia.toInt();
      // =  potencia,toInt();
      Serial.print(" grados: ");
      Serial.println(GradoJoystick);
      Serial.print(" potencia: ");
      Serial.println(car.potenciaMAX);
      potencia = map(potencia, 0, 10, 0, 255);
      if (GradoJoystick >= 45 && GradoJoystick < 135 ){
        // UP
      car.mover(potencia,potencia);
      delay(50);  
      }
      if (GradoJoystick >= 0 && GradoJoystick < 45 || GradoJoystick >= 335 && GradoJoystick < 359 ){
        // RIGHT
      car.mover(potencia,-potencia);
      delay(50);  
      }
      if (GradoJoystick >= 225 && GradoJoystick < 335){
        // DOWN
      car.mover(-potencia,-potencia);
      delay(50);  
      }
      if (GradoJoystick >= 135 && GradoJoystick < 225 ){
        // LEFT
      car.mover(-potencia,potencia);
      delay(50);  
      }
      
      
     break;     
  }
  
}
