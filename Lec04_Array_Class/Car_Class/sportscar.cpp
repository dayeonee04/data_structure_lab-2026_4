#include "SportsCar.h"

SportsCar::SportsCar() : bTurbo(false) {
    // 부모의 생성자가 먼저 호출된 후 실행됨
}

void SportsCar::setTurbo(bool bTur) {
    bTurbo = bTur;
}

void SportsCar::speedUp() {
    if (bTurbo) {
        speed += 20; // 터보 작동 시 가속량 증가
    }
    else {
        Car::speedUp(); // 부모의 기본 가속 함수 호출
    }
}