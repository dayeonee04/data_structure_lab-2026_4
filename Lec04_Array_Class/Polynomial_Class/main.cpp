#include "Polynomial.h"

void main() {
    Polynomial a, b, c;

    a.read();      // 다항식 a 입력
    b.read();      // 다항식 b 입력

    c.add(a, b);   // c = a + b

    a.display("A = ");
    b.display("B = ");
    c.display("A+B = ");
}