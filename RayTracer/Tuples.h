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

	int getType() const {
		return type;
	}

	vector<double> getAll() const {
		return vector<double>{ x, y, z, w };
	}

	void Print() {
		cout << x << " ";
		cout << " " << y << " ";
		cout << " " << z << " ";
		cout << " " << w << endl;
	}
};


struct Vector : Tuple {

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

	double magnitude() const;
	Vector normalize() const;
	double dot(Vector const& u) const;
	Vector cross(Vector const& u) const;

	Vector reflect(Vector incoming, Vector normal) {

		return incoming - normal * 2 * incoming.dot(normal);
	}

	Vector scale(double x) {

		Vector temp;

		temp.x *= x;
		temp.y *= x;
		temp.z *= x;
		temp.w *= x;

		return temp;
	}
};

struct Point : Tuple {

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
	Point operator-(Vector other);
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

	Color operator+(Color const& other) {

		return Color(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Color operator*(double const& other) {

		return Color(this->x * other, this->y * other, this->z * other);
	}

	Color operator*(Color const& other) {

		return Color(this->x * other.x, this->y * other.y, this->z * other.z);
	}
};
