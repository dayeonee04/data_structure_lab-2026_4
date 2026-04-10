#include "SportsCar.h"

int main() {
    SportsCar myCar;

    myCar.setTurbo(true);
    myCar.changeGear(5);
    myCar.speedUp(); // SportsCar의 오버라이딩된 함수 호출

    myCar.display();  // 부모 클래스의 함수 사용
    myCar.whereAmI(); // this 포인터 확인

    return 0;
}