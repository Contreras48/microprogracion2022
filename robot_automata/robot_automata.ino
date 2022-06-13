#include "RobotCar.h"
Carro car;
int detener = 20;
int giro = 45;

void setup(){
    Serial.begin(9600);
    car.potenciaMAX = 220;
}

void loop(){
//    if (car.UltraC->medir() > detener)
//    {
//        car.mover(10,10);
//    }else{
//        car.mover(0,0);
//        delay(100);
//        car.UltraI->medir() > car.UltraD->medir() ? car.girar(giro) : car.girar(-1*giro);
//    }

    if (car.UltraC->medir() < detener)
    {
        car.mover(0,0);
        delay(100);
        car.UltraI->medir() > car.UltraD->medir() ? car.girar(giro) : car.girar(-1*giro);
    }

    if (car.UltraI->medir() < detener){
        car.mover(0,0);
        delay(100);
        car.girar(giro);
    }
    if (car.UltraD->medir() < detener){
        car.mover(0,0);
        delay(100);
        car.girar(-1*giro);
    }

    car.mover(10,10);

    Serial.print("rueda izqierda: ");
    Serial.println(car.contaI);
    Serial.print("rueda derecha: ");
    Serial.println(car.contaD);
}
