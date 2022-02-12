#pragma once
#include <iostream>
#include <vector>
#include <iomanip> 

using namespace std;

struct Tuple {

	float x;
	float y;
	float z;
	float w;
	int type;

	Tuple();

	int getType() const {
		return type;
	}

	vector<float> getAll() const {
		return vector<float>{ x, y, z, w };
	}

	void Print() {
		cout << x << " ";
		cout << " " << y << " ";
		cout << " " << z << " ";
		cout << " " << w << endl;
	}
};


struct Vector : Tuple {

	Vector(float r = 0, float g = 0, float b = 0) {
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
	Vector operator*(float num) const;
	Vector operator*(Vector const& other) const;
	Vector operator/(float num) const;
	Vector operator/(Vector const& other) const;

	float magnitude() const;
	Vector normalize() const;
	float dot(Vector const& u) const;
	Vector cross(Vector const& u) const;

	Vector reflect(Vector incoming, Vector normal) {

		return incoming - normal * 2 * incoming.dot(normal);
	}

	Vector scale(float x) {

		Vector temp;

		temp.x *= x;
		temp.y *= x;
		temp.z *= x;
		temp.w *= x;

		return temp;
	}
};

struct Point : Tuple {

	Point(float r = 0, float g = 0, float b = 0) {

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
	Point operator*(float num) const;
	Point operator*(Point const& other) const;
	Point operator/(float num) const;
	Point operator/(Point const& other) const;
};


struct Color : public Tuple {
	Color(float r = 0, float g = 0, float b = 0, float o = 1) {

		x = r;
		y = g;
		z = b;
		w = o;
		type = 2;
	}

	Color operator+(Color const& other) {

		return Color(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Color operator*(float const& other) {

		return Color(this->x * other, this->y * other, this->z * other);
	}

	Color operator*(Color const& other) {

		return Color(this->x * other.x, this->y * other.y, this->z * other.z);
	}
};
