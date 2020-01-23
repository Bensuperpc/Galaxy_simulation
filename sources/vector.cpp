#include "vector.h"
#include "utils.h"



// Construit un vecteur

Vector::Vector()
{
	x = 0.;
	y = 0.;
	z = 0.;
}



// Construit un vecteur � partir d'un autre vecteur

Vector::Vector(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}



// Construit un vecteur � partir de ses coordonn�es cart�siennes

Vector::Vector(const double& x, const double& y, const double& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}



// Construit un vecteur � partir de ses coordonn�es sph�riques

Vector create_spherical(const double& radius, const double& phi, const double& theta)
{
	return Vector(get_x(radius, phi, theta), get_y(radius, phi, theta), get_z(radius, phi, theta));
}



// Assignations

void Vector::operator=(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector::operator+=(const Vector& vector)
{
	*this = *this + vector;
}

void Vector::operator-=(const Vector& vector)
{
	*this = *this - vector;
}

void Vector::operator*=(const double& number)
{
	*this = *this * number;
}

void Vector::operator/=(const double& number)
{
	*this = *this / number;
}



// Addition

Vector operator+(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z);
}



// Soustraction

Vector operator-(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z);
}



// Produit

Vector operator*(const Vector& vector, const double& number)
{
	return Vector(vector.x * number, vector.y * number, vector.z * number);
}

Vector operator*(const double& number, const Vector& vector)
{
	return Vector(number * vector.x, number * vector.y, number * vector.z);
}



// Produit scalaire

double operator*(const Vector& vector_1, const Vector& vector_2)
{
	return vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
}



// Produit vectoriel

Vector operator^(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.y * vector_2.z - vector_1.z * vector_2.y, vector_1.z * vector_2.x - vector_1.x * vector_2.z, vector_1.x * vector_2.y - vector_1.y * vector_2.x);
}



// Division

Vector operator/(const Vector& vector, const double& number)
{
	return Vector(vector.x / number, vector.y / number, vector.z / number);
}



// Egalit�s

bool operator==(const Vector& vector_1, const Vector& vector_2)
{
	return (vector_1.x == vector_2.x and vector_1.y == vector_2.y and vector_1.z == vector_2.z);
}

bool operator!=(const Vector& vector_1, const Vector& vector_2)
{
	return (!(vector_1.x == vector_2.x and vector_1.y == vector_2.y and vector_1.z == vector_2.z));
}



// Donne la norme du vecteur (en m�tres)

double Vector::get_radius() const
{
	return sqrt(x * x + y * y + z * z);
}



// Donne l'angle phi du vecteur (en radiants)

double Vector::get_phi() const
{
	Vector vector = *this;

	vector.z = 0.;

	if (vector.y > 0)
		return acos(vector.x / vector.get_radius());

	if (vector.y < 0)
		return 2 * PI - acos(vector.x / vector.get_radius());
}



// Donne l'angle theta du vecteur (en radiants)

double Vector::get_theta() const
{
	return acos(z / get_radius());
}



// Donne la valeur cart�sienne x � partir des coordonn�es sph�riques (en m�tres)

double get_x(const double& radius, const double& phi, const double& theta)
{
	return cos(phi) * sin(theta) * radius;
}



// Donne la valeur cart�sienne y � partir des coordonn�es sph�riques (en m�tres)

double get_y(const double& radius, const double& phi, const double& theta)
{
	return sin(phi) * sin(theta) * radius;
}



// Donne la valeur cart�sienne z � partir des coordonn�es sph�riques (en m�tres)

double get_z(const double& radius, const double& phi, const double& theta)
{
	return cos(theta) * radius;
}



// Donne la distance entre deux points (en m�tres)

double get_distance(const Vector& point_1, const Vector& point_2)
{
	return (point_1 - point_2).get_radius();
}



// Donne l'angle phi entre deux points (en radiants)

double get_phi(const Vector& point_1, const Vector& point_2)
{
	return (point_1 - point_2).get_phi();
}



// Donne l'angle theta entre deux points (en radiants)

double get_theta(const Vector& point_1, const Vector& point_2)
{
	return (point_1 - point_2).get_theta();
}



// Donne le vecteur normalis�

Vector normalize(const Vector& vector)
{
	return vector / vector.get_radius();
}