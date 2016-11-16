#include "Complex.h"

Complex::Complex() {
    Complex::real = 0;
    Complex::imag = 0;
}

Complex::Complex(int r, int c) {
    Complex::real = r;
    Complex::imag = c;
}

Complex Complex::getReal() {
    return this->real;
}

Complex Complex::getImag() {
    return this->imag;
}

Complex Complex::operator+(Complex c) {
    Complex ret(this->real + c.getReal(), this->imag + c.getImag());
    return ret;
}

Complex Complex::operator-(Complex c) {
    Complex ret(this->real - c.getReal(), this->imag - c.getImag());
    return ret;
}

Complex Complex::operator+=(Complex c) {
    this = this + c;
    return this;
}

Complex Complex::operator-=(Complex c) {
    this = this - c;
    return this;
}