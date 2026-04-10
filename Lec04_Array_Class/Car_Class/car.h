#pragma once
#ifndef CAR_H
#define CAR_H

#include <cstdio>
#include <cstring>

class Car {
protected:
    int speed;          // 자식 클래스에서 접근 가능
    char name[40];

public:
    int gear;

    // 생성자 및 소멸자
    Car();
    ~Car();
    Car(int s, const char* n, int g);

    // 멤버 함수
    void changeGear(int g = 4); // 디폴트 매개변수
    void speedUp();
    void display();
    void whereAmI();
};

#endif