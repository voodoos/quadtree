#pragma once

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

template <typename T>
class Vector {
private:
	T m_theta;
	T m_n;
public:
	Vector(T x, T y) : Vector<T>(sf::Vector2<T>(x, y)) {}
	Vector(sf::Vector2<T> v) : Vector<T>(v.x, v.y, computeNorm(v)) {}
	Vector(sf::Vector2<T> d, T n) : Vector<T>(d.x, d.y, n) {}
	Vector(T n) : Vector<T>(0.f, 0.f, n) {}
	Vector(T x, T y, T n) : m_n(n) {
		setAngle(sf::Vector2<T>(x, y));
	}

	/*
	Vector(const Vector<T>& v) : Vector<T>(v.getDirection(), v.getNorm()) {
		std::cout << "copy!" << std::endl;
	}
	Vector<T>& operator=(Vector<T>&& v) {
		std::cout << "move!" << std::endl;
		return *this;
	}*/


	static T computeNorm(sf::Vector2<T> v) {
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	static T computeAngle(sf::Vector2<T> v) {
		if (v.x == 0) {
			if (v.y >= 0) return (T)M_PI_2;
			return -(T)M_PI_2;
		}
		else if (v.y == 0) {
			if (v.x >= 0) return 0;
			else return (T)M_PI;
		}
		else {
			T val = v.x / computeNorm(v);

			if (v.y > 0) return acos(val);
			else return -acos(val);
		}
	}

	sf::Vector2<T> getSfVector() const {
		return sf::Vector2<T>(x(), y()) * m_n;
	}

	T x() const {
		return cos(m_theta);
	}

	T y() const {
		return sin(m_theta);
	}


	T getAngle() const {
		return m_theta;
	}

	T getNorm() const {
		return m_n;
	}

	void setAngle(T a) {
		m_theta = a;
	}
	void setAngle(sf::Vector2<T> v) {
		setAngle(computeAngle(v));
	}


	void setNorm(T n) {
		m_n = n;
	}

	std::string toString() const {
		std::stringstream s;
		s << m_theta << ", " << m_n;
		return s.str();
	}

	/*
	Vector<T> & operator=(const Vector<T> &copy) {
		std::cout << "copyAssign!" << std::endl;
		m_x = copy.m_x;
		m_y = copy.m_y;
		m_n = copy.m_n;
		return *this;
	}*/

	Vector<T>& operator- () {
		m_n = -m_n;
		return *this;
	}

	Vector<T>& operator* (T n) {
		m_n *= n;
		return *this;
	}

	Vector<T>& operator/ (T n) {
		m_n /= n;
		return *this;
	}

	Vector<T>& operator+ (T a) {
		m_theta += a;
		return *this;
	}

	Vector<T>& operator+= (T a) {
		m_theta += a;
		return *this;
	}

	Vector<T>& operator-= (T a) {
		m_theta -= a;
		return *this;
	}
};
using VectorF = Vector<float>;
using VectorI = Vector<int>;
using VectorD = Vector<double>;
