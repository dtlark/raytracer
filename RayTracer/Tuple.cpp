#include "Tuple.h"

Tuple::Tuple() {};

Tuple::Tuple(double x, double y, double z, int w) {

	if (w == 1) {
		Point(x, y, z);
	}
	else {
		Vector(x, y, z);
	}
}

//bool Tuple::IsPoint() const {
//	if (w == 1) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//bool Tuple::IsVector() const {
//	if (w == 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//bool Tuple::IsColor() const {
//
//	if (w == 2) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

//magnitude (v): length of a tuple
double Tuple::magnitude() const {
	return sqrt(pow(x, 2) + 
				pow(y, 2) + 
				pow(z, 2));
}

//normalization: converting a vector to a unit vector (vector of magnitude 1) 
Tuple Tuple::normalize() const {

	double mag = magnitude();
	return Tuple(x / mag,
				 y / mag,
				 z / mag,
				 w / mag);
}

//dot product: the smaller the dot product the larger the angle between vectors 
double Tuple::dot(Tuple const& u) const {

	return this->x * u.x +
		   this->y * u.y +
		   this->z * u.z;
}

//cross product: returns vector perpendicular to both vectors
Tuple Tuple::cross(Tuple const& t, Tuple const& u) const {
	Vector temp = Vector(t.y / u.z - t.z / u.y,
						 t.z / u.x - t.x / u.z,
						 t.x / u.y - t.y / u.x);
	return temp;
}



// assign tuples
void Vector::operator=(Vector const& other) {

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

// compare tuples
bool Vector::operator==(Vector const& other) const {
	if (x == other.x && y == other.y && z == other.z) {
		return true;
	}
	else {
		return false;
	}
}
//add tuples : point + Point is invalid
Vector Vector::operator+(Vector const& other) const {
	double _x = x + other.x;
	double _y = y + other.y;
	double _z = z + other.z;
	return Vector(_x, _y, _z);
}
//subtracting tuples : Vector - Point is invalid
Vector Vector::operator-(Vector const& other) const {

	double _x = x - other.x;
	double _y = y - other.y;
	double _z = z - other.z;

	return Vector(_x, _y, _z);
}
//negating tuples
Vector Vector::operator-() const {

	double _x = 0 - x;
	double _y = 0 - y;
	double _z = 0 - z;

	return Vector(_x, _y, _z);
}
//scalar multiplication
Vector Vector::operator*(double num) const {

	double _x = x * num;
	double _y = y * num;
	double _z = z * num;

	return Vector(_x, _y, _z);
}
Vector Vector::operator*(Vector const& other) const {

	double _x = x * other.x;
	double _y = y * other.y;
	double _z = z * other.z;

	return Vector(_x, _y, _z);
}
//scalar division
Vector Vector::operator/(double num) const {

	double _x = x / num;
	double _y = y / num;
	double _z = z / num;

	return Vector(_x, _y, _z);
}
Vector Vector::operator/(Vector const& other) const {

	double _x = x / other.x;
	double _y = y / other.y;
	double _z = z / other.z;

	return Vector(_x, _y, _z);
}



// assign
void Point::operator=(Point const& other) {

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

// equality
bool Point::operator==(Point const& other) const {

	if (x == other.x && y == other.y && z == other.z) {
		return true;
	}
	else {
		return false;
	}
}

// addition : Point(1) + Point(1) is invalid
Point Point::operator+(Point const& other) const {

	double _x = x + other.x;
	double _y = y + other.y;
	double _z = z + other.z;

	return Point(_x, _y, _z);
}

Point Point::operator+(Vector const& other) const {

	double _x = x + other.x;
	double _y = y + other.y;
	double _z = z + other.z;

	return Point(_x, _y, _z);
}

//subtracting tuples : //Vector(0) - Point(1) is invalid
Point Point::minus(Point me, Point other) {

	double _x = me.x - other.x;
	double _y = me.y - other.y;
	double _z = me.z - other.z;

	return Point(_x, _y, _z);
}

Vector Point::operator-(Point other) {

	double _x = x - other.x;
	double _y = y - other.y;
	double _z = z - other.z;

	return Vector(_x, _y, _z);
}

//negating tuples
Point Point::operator-() const {

	double _x = 0 - x;
	double _y = 0 - y;
	double _z = 0 - z;

	return Point(_x, _y, _z);
}

//scalar multiplication
Point Point::operator*(double num) const {

	double _x = x * num;
	double _y = y * num;
	double _z = z * num;

	return Point(_x, _y, _z);
}

Point Point::operator*(Point const& other) const {

	double _x = x * other.x;
	double _y = y * other.y;
	double _z = z * other.z;

	return Point(_x, _y, _z);
}

//scalar division
Point Point::operator/(double num) const {

	double _x = x / num;
	double _y = y / num;
	double _z = z / num;

	return Point(_x, _y, _z);
}

Point Point::operator/(Point const& other) const {

	double _x = x / other.x;
	double _y = y / other.y;
	double _z = z / other.z;

	return Point(_x, _y, _z);
}

