#include "Tuples.h"

Tuple::Tuple() {};


/* Vector */

// assign tuples
void Vector::operator=(Vector const& other) {

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

// compare tuples
bool Vector::operator==(Vector const& other) const {

	return(x == other.x && 
		   y == other.y && 
		   z == other.z);
}

//add tuples : point + Point is invalid
Vector Vector::operator+(Vector const& other) const {

	return Vector(x + other.x, y + other.y, z + other.z);
}

//subtracting tuples : Vector - Point is invalid
Vector Vector::operator-(Vector const& other) const {

	return Vector(x - other.x, y - other.y, z - other.z);
}

//negating tuples
Vector Vector::operator-() const {

	return Vector(-x, -y, -z);
}

//scalar multiplication
Vector Vector::operator*(float num) const {

	return Vector(x * num, y * num, z * num);
}
Vector Vector::operator*(Vector const& other) const {

	return Vector(x * other.x, y * other.y, z * other.z);
}

//scalar division
Vector Vector::operator/(float num) const {

	float _x = x / num;
	float _y = y / num;
	float _z = z / num;

	return Vector(x / num, y / num, z / num);
}
Vector Vector::operator/(Vector const& other) const {

	float _x = x / other.x;
	float _y = y / other.y;
	float _z = z / other.z;

	return Vector(x / other.x, y / other.y, z / other.z);
}

//magnitude (v): length of a tuple
float Vector::magnitude() const {
	return sqrt(pow(x, 2) +
		pow(y, 2) +
		pow(z, 2));
}

//normalization: converting a vector to a unit vector (vector of magnitude 1) 
Vector Vector::normalize() const {
	float mag = magnitude();
	return Vector(x / mag,
				  y / mag,
				  z / mag);
}

//dot product: the smaller the dot product the larger the angle between vectors 
float Vector::dot(Vector const& u) const {
	return this->x * u.x +
			this->y * u.y +
			this->z * u.z;
}

//cross product: returns vector perpendicular to both vectors
Vector Vector::cross(Vector const& u) const {
	return Vector(this->y / u.z - this->z / u.y,
				  this->z / u.x - this->x / u.z,
				  this->x / u.y - this->y / u.x);
}





/* Point */

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

	return Point(x + other.x, y + other.y, z + other.z);
}
Point Point::operator+(Vector const& other) const {

	return Point(x + other.x, y + other.y, z + other.z);
}

//subtraction
Vector Point::operator-(Point other) {

	return Vector(x - other.x, y - other.y, z - other.z);
}
Point Point::operator-(Vector other) {

	return Point(x - other.x, y - other.y, z - other.z);
}


//negating tuples
Point Point::operator-() const {

	return Point(-x, -y, -z);
}

//scalar multiplication
Point Point::operator*(float num) const {

	return Point(x * num, y * num, z * num);
}
Point Point::operator*(Point const& other) const {

	return Point(x * other.x, y * other.y, z * other.z);
}

//scalar division
Point Point::operator/(float num) const {

	return Point(x / num, y / num, z / num);
}
Point Point::operator/(Point const& other) const {

	return Point(x / other.x, y / other.y, z / other.z);
}

