#pragma once
#ifndef SPORTSCAR_H
#define SPORTSCAR_H

#include "Car.h"

class SportsCar : public Car {
public:
    bool bTurbo; // 터보 장치 ON/OFF

    SportsCar();
    void setTurbo(bool bTur);
    void speedUp(); // 함수 오버라이딩
};

#endif