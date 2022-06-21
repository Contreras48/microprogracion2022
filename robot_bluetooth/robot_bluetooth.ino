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
           //Serial.println(DatoBT);
     } 
           
  if (Serial.available()){
        mySerial.write(Serial.read());
  }
}

void Driver(){
  
  int grados = DatoBT.substring(0,3).toInt();
  int potencia = DatoBT.substring(3,6).toInt(); //configuración 1
  boton = DatoBT.charAt(6); 
  int diferencia = 2;
  //Serial.println(grados);
  //Serial.println(boton);


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
      //int GradoJoystick = grados.toInt();
      //int PotMotor = potencia.toInt();
      // =  potencia,toInt();
      Serial.print(" grados: ");
      Serial.println(grados);
//      Serial.print(" potencia: ");
//      Serial.println(car.potenciaMAX);
      potencia = map(potencia, 0, 100, 0, 10);
      Serial.print("Potencia ");
      Serial.println(potencia);
//      if (GradoJoystick >= 45 && GradoJoystick < 135 ){
//        // UP
//      car.mover(potencia,potencia);
//      delay(50);  
//      }
//      if (GradoJoystick >= 0 && GradoJoystick < 45 || GradoJoystick >= 335 && GradoJoystick < 359 ){
//        // RIGHT
//      car.mover(potencia,-potencia);
//      delay(50);  
//      }
//      if (GradoJoystick >= 225 && GradoJoystick < 335){
//        // DOWN
//      car.mover(-potencia,-potencia);
//      delay(50);  
//      }
//      if (GradoJoystick >= 135 && GradoJoystick < 225 ){
//        // LEFT
//      car.mover(-potencia,potencia);
//      delay(50);  
//      }

      //confiiguración 1
//      if(grados >= 0 && grados <= 90){
//        car.mover(potencia,potencia - (diferencia(grados, potencia)));
//        delay(50);
//        Serial.print("velocidad ");
//        Serial.println(diferencia(grados, potencia));
//        Serial.print("... ");
//      }
//      if(grados > 90 && grados <= 180){
//        int x = (int)(potencia * sin(grados));
//        car.mover(x,potencia);
//        delay(50);
//        Serial.print("velocidad ");
//        Serial.println(x);
//        Serial.print("... ");
//      }
//      if(grados > 180 && grados <= 270){
//        int x = (int)(potencia * cos(grados));
//        car.mover((-potencia - (x)) ,-potencia );
//        delay(50);
//        Serial.print("velocidad ");
//        Serial.println(x);
//        Serial.print("... ");
//      }if(grados > 270 && grados <= 359){
//        int x = (int)(potencia * sin(grados));
//        car.mover(-potencia,x );
//        delay(50);
//        Serial.print("velocidad ");
//        Serial.println(x);
//        Serial.print("... ");
//      }

     //configuración
     if(grados >= 338 || grados <= 22){
      //derecha
      car.mover(potencia, 0);
      delay(50);
      Serial.println("derecha");
     }
     else if(grados > 22 && grados < 67){
      //arriba derecha
      car.mover(potencia, velocidad(potencia));
      delay(50);
      Serial.println("arriba derecha");
     }
     else if(grados >= 67 && grados <= 112){
      //arriba
      car.mover(potencia, potencia);
      delay(50);
      Serial.println("arriba");
     }
     else if(grados > 112 && grados < 157){
      //arriba izquierda
      car.mover(velocidad(potencia), potencia);
      delay(50);
      Serial.println("arriba izquierda");
     }
     else if(grados >= 157 && grados <= 202){
      //izquierda
      car.mover(0, potencia);
      delay(50);
      Serial.println("izquierda");
     }
     else if(grados > 202 && grados < 247){
      //abajo izquierda
      car.mover(-velocidad(potencia), -potencia);
      delay(50);
      Serial.println("abajo izquierda");
     }
     else if(grados >= 247 && grados <= 292){
      //abajo
      car.mover(-potencia, -potencia);
      delay(50);
      Serial.println("abajo");
     }
     else if(grados > 292 && grados < 338){
      //abajo derecha
      car.mover(-potencia, -velocidad(potencia));
      delay(50);
      Serial.println("abajo derecha");
     }

        
      
     break;     
  }
  
}

int diferencia(int grados, int potencia){
  return (int)(potencia * cos(grados));
}

int velocidad(int potencia){
  if(potencia == 0){
    return 0;
  }
  return potencia - 2;
}
