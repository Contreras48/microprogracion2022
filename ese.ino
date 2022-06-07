#include "RobotCar.h"
Carro car;
int detener = 15;
int giro = 90;

void setup(){
    Serial.begin(9600);
    car.potenciaMAX = 220;
}

void loop(){
    if (car.UltraC->medir() > detener)
    {
        car.mover(10,10);
    }else{
        car.mover(0,0);
        delay(100);
        car.UltraI->medir() > car.UltraD->medir() ? car.girar(giro) : car.girar(-1*giro);
    }
}
