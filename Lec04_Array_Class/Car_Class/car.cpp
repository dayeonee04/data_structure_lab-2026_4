#include "Car.h"

// 기본 생성자
Car::Car() : speed(0), gear(1) {
    strcpy_s(name, "Car");
}

// 소멸자
Car::~Car() {}

// 매개변수가 있는 생성자 (멤버 초기화 리스트)
Car::Car(int s, const char* n, int g) : speed(s), gear(g) {
    strcpy_s(name, n);
}

void Car::changeGear(int g) {
    gear = g;
}

void Car::speedUp() {
    speed += 5;
}

void Car::display() {
    printf("[%s] : GEAR=%d speed =%dkm/h\n", name, gear, speed);
}

void Car::whereAmI() {
    printf("object adress = %p\n", this); // this 포인터 출력
}