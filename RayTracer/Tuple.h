#pragma once
#include <iostream>
#include <vector>
#include <iomanip> 

using namespace std;

struct Tuple {

	double x;
	double y;
	double z;
	double w;
	int type;

	Tuple();
	Tuple(double x, double y, double z, int w);

	double magnitude() const;
	Tuple normalize() const;
	double dot(Tuple const& u) const;
	Tuple cross(Tuple const& t, Tuple const& u) const;

	//bool IsPoint() const;
	//bool IsVector() const;
	//bool IsColor() const;

	int getType() const {
		return type;
	}

	vector<double> getAll() const {
		vector<double> temp = {x, y, z, w};
		return temp;
	}

	void Print() {
		cout << x << " ";
		cout << " " << y << " ";
		cout << " " << z << " ";
		cout << " " << w << endl;
	}
};


struct Vector : public Tuple {

	Vector(double r = 0, double g = 0, double b = 0) {
		x = r;
		y = g;
		z = b;
		w = 0;
		type = 0;
	}

	void operator=(Vector const& other);
	bool operator==(Vector const& other) const;
	Vector operator+(Vector const& other) const;
	Vector operator-(Vector const& other) const;
	Vector operator-() const;
	Vector operator*(double num) const;
	Vector operator*(Vector const& other) const;
	Vector operator/(double num) const;
	Vector operator/(Vector const& other) const;


	Vector normalize() const {
		double mag = this->magnitude();
		return Vector(x / mag,
			y / mag,
			z / mag);
	}
	Vector reflect(Vector incoming, Vector normal) {

		return incoming - normal * 2 * incoming.dot(normal);
	}

	//void setW(double w) {
	//	this->w = w;
	//}

	Vector scale(double x) {

		Vector temp;

		temp.x *= x;
		temp.y *= x;
		temp.z *= x;
		temp.w *= x;

		return temp;
	}

	//double dot(Vector const& u) const {

	//	return this->x * u.getX() +
	//		this->y * u.getY() +
	//		this->z * u.getZ() +
	//		this->w * u.getW();
	//};

	//double dot(Point const& u) const {

	//	return this->x * u.getX() +
	//		this->y * u.getY() +
	//		this->z * u.getZ() +
	//		this->w * u.getW();
	//};
};

struct Point : public Tuple {

	Point(double r = 0, double g = 0, double b = 0) {
		x = r;
		y = g;
		z = b;
		w = 1;
		type = 1;
	}

	void operator=(Point const& other);
	bool operator==(Point const& other) const;
	Point operator+(Point const& other) const; //TODO: Remove
	Point operator+(Vector const& other) const;
	Vector operator-(Point other);
	Point minus(Point me, Point other); //TODO: Fix this
	Point operator-() const;
	Point operator*(double num) const;
	Point operator*(Point const& other) const;
	Point operator/(double num) const;
	Point operator/(Point const& other) const;
};


struct Color : public Tuple {
	Color(double r = 0, double g = 0, double b = 0, double o = 1) {
		x = r;
		y = g;
		z = b;
		w = o;
		type = 2;
	}
	//Effect - Add: 2 Colors
	Color Add(Color color) {
		return Color(x + color.x,
			y + color.y,
			z + color.z);
	}
	//Effect - Subtract: 2 Colors
	Color Subtract(Color color) {
		return Color(x - color.x,
			y - color.y,
			z - color.z);
	}
	//Effect - Multiply: 2 Colors (Hadamard Product)
	Color Multiply(Color color) {
		return Color(x * color.x,
			y * color.y,
			z * color.z);
	}
	//Effect - Multiply: Scalar Multiplication
	Color Multiply(double val) {
		return Color(x * val,
			y * val,
			z * val);
	}

	void Normalize() {

	};

	Color operator*(double const& other) {
		double _x = this->x * other;
		double _y = this->y * other;
		double _z = this->z * other;
		return Color(_x, _y, _z);
	}

	Color operator+(Color const& other) {
		double _x = this->x + other.x;
		double _y = this->y + other.y;
		double _z = this->z + other.z;
		return Color(_x, _y, _z);
	}

	Color operator*(Color const& other) {
		double _x = this->x * other.x;
		double _y = this->y * other.y;
		double _z = this->z * other.z;
		return Color(_x, _y, _z);
	}
};
