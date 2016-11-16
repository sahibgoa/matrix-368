#ifndef MATRIX_368_COMPLEX_H
#define MATRIX_368_COMPLEX_H

class Complex {
private:
    int real;
    int imag;
public:
    Complex();
    Complex(int r, int c);
    Complex getReal();
    Complex getImag();
    Complex operator+(Complex c);
    Complex operator-(Complex c);
    Complex operator+=(Complex c);
    Complex operator-=(Complex c);
};

#endif //MATRIX_368_COMPLEX_H
