#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cstdio>

#define MAX_DEGREE 80 // 다항식의 최대 차수 + 1

class Polynomial {
    int degree;                // 다항식의 최고 차수
    float coef[MAX_DEGREE];    // 각 항의 계수

public:
    // 생성자: 최고 차수를 0으로 초기화
    Polynomial() { degree = 0; }

    // 멤버 함수 선언
    void read();
    void display(const char* str = "Poly = ");
    void add(Polynomial a, Polynomial b);
    bool isZero() { return degree == 0; }
    void negate(); // 모든 계수의 부호를 바꿈
};

#endif