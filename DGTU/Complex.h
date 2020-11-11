#pragma once
#include <iostream>
class Complex {
public:
	Complex() : im(0), real(0) {}
	Complex(double _real, double _im) : im(_im), real(_real) {}
	Complex(const Complex& c) : im(c.im), real(c.real), number{ &real, &im }{}
	Complex(Complex& c) : im(c.im), real(c.real), number{ &real, &im }{}

	friend std::ostream& operator<<(std::ostream& out, const Complex& c) {
		out << c.real << ((c.im >= 0) ? '+' : '-') << std::fabs(c.im) << 'i';
		return out;
	}
	friend const Complex operator^(Complex& c, const int lvl) {
		const double fin = std::atan(c.im / c.real) * lvl;
		const double mod = static_cast<const double>(c);
		const double ratio = std::pow(mod, lvl);
		return Complex(ratio * std::cos(fin), ratio * std::sin(fin));
	}
	friend const Complex operator+(const Complex& left, const Complex& right) {
		return Complex(left.real + right.real, left.im + right.im);
	}
	friend const Complex operator-(const Complex& left, const Complex& right) {
		return Complex(left.real - right.real, left.im - right.im);
	}
	friend const bool operator==(const Complex& left, const Complex& right) {
		return left.im == right.im && left.real == right.real;
	}
	friend const Complex operator*(const Complex& left, const Complex& right) {
		return Complex(left.real * right.real - left.im * right.im, left.real * right.im + right.real * left.im);
	}
	const double operator()(const int index) {
		return *(number[index]);
	}
	const double operator[](const int index) {
		return *(number[index]);
	}
	operator double() {
		return std::pow(im * im + real * real, 0.5);
	}
private:
	double im;
	double real;
	double* number[2]{ &real, &im };
};

