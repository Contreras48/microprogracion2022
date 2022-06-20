
// Proyecto Robot controlado por módulo Hc-05
// Automata Canal: https://www.youtube.com/channel/UCKD9PvMAW0nYi681AZbSZSQ?view_as=subscriber
// suscribete !!!

String DatoBT;
char boton;


void setup()
  {
      Serial.begin(9600);
      Serial1.begin(9600);

      // Salidas PWM para el PuenteH 
      pinMode(2, OUTPUT);  // UP MotorL
      pinMode(3, OUTPUT);  // DOWN MotorL 
      pinMode(4, OUTPUT);  // DOWN MotorR
      pinMode(5, OUTPUT);   // UP MotorR

      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW); 
      delay(1000);

  }
 
void loop()
  {  
    BTfuncion();
    
  }

  

// funcion de lectura Bluetooth

void BTfuncion (){
  if (Serial1.available()>0){
           DatoBT= Serial1.readStringUntil('#');
           Driver();
           Serial.println(DatoBT);
     } 
           
  if (Serial.available()){
        Serial1.write(Serial.read());
  }
}

// funcion para controlar posicion del servo

void Driver(){
  
  String Grados = DatoBT.substring(0,3);
  String Potencia = DatoBT.substring(3,6);
  boton = DatoBT.charAt(6); 
  Serial.println(Grados);
  Serial.println(boton);


  switch (boton){
    case '1':  // LEFT
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      delay(70);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
     break;
    case '4':   // UP
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      delay(70);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);      
     break;  
    case '3':  // RIGHT
      digitalWrite(2, HIGH);
      digitalWrite(5, HIGH);
      delay(70);
      digitalWrite(2, LOW);
      digitalWrite(5, LOW);       
     break;   
    case '2':  // dowm
      digitalWrite(2, HIGH);
      digitalWrite(4, HIGH);
      delay(70);
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);  
     break;   
     case '0': 
      int GradoJoystick = Grados.toInt();
      int PotMotor = Potencia.toInt();
      Serial.print(" Grados: ");
      Serial.println(GradoJoystick);
      Serial.print(" Potencia: ");
      Serial.println(PotMotor);
      int valorMapeado = map(PotMotor, 0, 100, 0, 255);
      if (GradoJoystick >= 45 && GradoJoystick < 135 ){
        // UP
      analogWrite(3, valorMapeado);
      analogWrite(5, valorMapeado);
      delay(50);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);  
      }
      if (GradoJoystick >= 0 && GradoJoystick < 45 || GradoJoystick >= 335 && GradoJoystick < 359 ){
        // RIGHT
      analogWrite(2, valorMapeado);
      analogWrite(5, valorMapeado);
      delay(50);
      digitalWrite(2, LOW);
      digitalWrite(5, LOW);
      }
      if (GradoJoystick >= 225 && GradoJoystick < 335){
        // DOWN
      analogWrite(2, valorMapeado);
      analogWrite(4, valorMapeado);
      delay(50);
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      }
      if (GradoJoystick >= 135 && GradoJoystick < 225 ){
        // LEFT
      analogWrite(3, valorMapeado);
      analogWrite(4, valorMapeado);
      delay(50);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      }
      
      
     break;     
  }
  
}
