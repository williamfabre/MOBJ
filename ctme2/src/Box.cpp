#include <iostream>
#include "Box.h"

using namespace std;
using namespace tme2;

int Box::count = 0;

/* Constructor and destructor */
/* Declaration du constructeur avec des valeur par defaut
 * on utilise : pour les signifier, nom de la variable de classe suivie
 * de entre parenthese la valeur
 */
Box::Box() :
	name_("Unknow"), x1_(1), y1_(1), x2_(-1), y2_(-1)
{
	count++;
	cerr << "Debug: Box::Box() "; print(cerr); cerr << endl;
}

Box::Box(string name, long x1, long y1, long x2, long y2) :
	name_(name), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{
	count++;
	cerr << "Debug: Box::Box(std::string, ...) "; print(cerr); cerr << endl;
}

Box::Box(const Box& other) :
	name_(other.name_), x1_(other.x1_), y1_(other.y1_),
	x2_(other.x2_), y2_(other.y2_)
{
	count++;
	name_ += "_c";
	cerr << "Debug: Box::Box(const Box&) "; print(cerr); cerr << endl;
}

/* tilde pour signifier que c'est le destructeur */
Box::~Box()
{
	count--;
	cerr << "Debug: Box::~Box() "; print(cerr); cerr << endl;
}

/* To string definition the print that is used to the << operator Allowing
 * out new object to have some decent print. preparation for overload
 * operator
 */
void Box::print(std::ostream& o) const
{
	std::string str;
	str = str + "<\"" + name_ + "\""
		+ "[" + std::to_string(x1_)
		+ " " + std::to_string(y1_)
		+ " " + std::to_string(x2_)
		+ " " + std::to_string(y2_) + "]>";
	o << str;
}

/* Check si pour notre boite, x1+(abscisse max) va collisionner avec le x
 * CF pour les autres coordonnees.
 */
bool Box::intersect(const Box& other) const
{
	if (isEmpty() || other.isEmpty()) return 0;

	if (	(x2_ <= other.x1_)
		|| (x1_ >= other.x2_)
		|| (y2_ <= other.y1_)
		|| (y1_ >= other.y2_)) return 0;
	return 1;
}

void Box::makeEmpty()
{
	x1_ = 1;
	y1_ = 1;
	x2_ = -1;
	y2_ = -1;
}

void Box::inflate(long dxy)
{
	x1_ -= dxy;
	y1_ -= dxy;
	x2_ += dxy;
	y2_ += dxy;
	((x2_ <= x1_) || (y2_ <= y1_)) ? makeEmpty(): void();
}

void Box::inflate (long dx, long dy)
{
	x1_ -= dx;
	y1_ -= dy;
	x2_ += dx;
	y2_ += dy;
	((x2_ <= x1_) || (y2_ <= y1_)) ? makeEmpty(): void();
}

void Box::inflate(long dx1, long dy1, long dx2, long dy2)
{
	x1_ -= dx1;
	y1_ -= dy1;
	x2_ += dx2;
	y2_ += dy2;
	((x2_ <= x1_) || (y2_ <= y1_)) ? makeEmpty(): void();
}

/* Test avec et sans const pour voir le passage par reference ou le passage par
 * copies
 */
Box Box::getIntersection(const Box& other) const
//Box Box::getIntersection(Box& other)
{
	if (intersect(other)) {
		std::string name = name_ + "_" + other.name_;
		return Box(name,
			   std::max(x1_, other.x1_),
			   std::max(y1_, other.y1_),
			   std::max(x2_, other.x2_),
			   std::max(y2_, other.y2_));
	}
	return Box();
}

/* Overload operator so he can handle intersection */
Box Box::operator&&(Box& other)
{
	return getIntersection(other);
}
