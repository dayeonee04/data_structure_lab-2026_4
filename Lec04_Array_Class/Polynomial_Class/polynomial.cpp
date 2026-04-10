#define _CRT_SECURE_NO_WARNINGS
#include "Polynomial.h"
#include <iostream>

// 다항식의 내용을 입력받는 함수
void Polynomial::read() {
    printf("Enter the degree of a polynomial: ");
    scanf("%d", &degree);
    printf("Enter the coefficients for each term(Total of % d) : ", degree + 1);
    for (int i = 0; i <= degree; i++) {
        scanf("%f", &coef[i]);
    }
}

// 다항식의 내용을 화면에 출력하는 함수
void Polynomial::display(const char* str) {
    printf("%s", str);
    for (int i = 0; i < degree; i++) {
        printf("%5.1f x^%d + ", coef[i], degree - i);
    }
    printf("%4.1f\n", coef[degree]);
}

// 다항식 a와 b를 더하는 함수 (c = a + b)
void Polynomial::add(Polynomial a, Polynomial b) {
    if (a.degree > b.degree) {
        *this = a; // 우선 차수가 높은 a를 자신에게 복사
        for (int i = 0; i <= b.degree; i++) {
            // 차수 차이만큼 인덱스를 조절하여 더함
            coef[i + (degree - b.degree)] += b.coef[i];
        }
    }
    else {
        *this = b; // 차수가 높거나 같은 b를 자신에게 복사
        for (int i = 0; i <= a.degree; i++) {
            coef[i + (degree - a.degree)] += a.coef[i];
        }
    }
}

// 모든 계수의 부호를 반전
void Polynomial::negate() {
    for (int i = 0; i <= degree; i++) {
        coef[i] = -coef[i];
    }
}