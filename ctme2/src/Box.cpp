#include <iostream>
#include "Box.h"

using namespace std;
using namespace tme2;

// Ne pas oublier d'initialiser et declarer ici.
int Box::count = 0;
int tme1Qf::Box::count = 0;

/****************************************************************************/
/************************** FirstBox definition *****************************/
/****************************************************************************/


/* Constructor and destructor */
/* Declaration du constructeur avec des valeur par defaut
 * on utilise : pour les signifier, nom de la variable de classe suivie
 * de entre parenthese la valeur
 */
Box::Box() :
	name_("Unknow"), x1_(1), y1_(1), x2_(-1), y2_(-1)
{
	count++;
	cerr << "Debug: Box::Box() " << *this << endl;
}

Box::Box(string name, long x1, long y1, long x2, long y2) :
	name_(name), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{
	count++;
	cerr << "Debug: Box::Box(std::string, ...) " << *this << endl;
}

Box::Box(const Box& other) :
	name_(other.name_), x1_(other.x1_), y1_(other.y1_),
	x2_(other.x2_), y2_(other.y2_)
{
	count++;
	name_ += "_c";
	cerr << "Debug: Box::Box(const Box&) " << *this << endl;
}

/* tilde pour signifier que c'est le destructeur */
Box::~Box()
{
	count--;
	cerr << "Debug: Box::~Box() " << *this << endl;
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

Box& Box::makeEmpty()
{
	x1_ = 1;
	y1_ = 1;
	x2_ = -1;
	y2_ = -1;
	return *this;
}

Box& Box::inflate(long dxy)
{
	x1_ -= dxy;
	y1_ -= dxy;
	x2_ += dxy;
	y2_ += dxy;
	return *this;
}

Box& Box::inflate (long dx, long dy)
{
	x1_ -= dx;
	y1_ -= dy;
	x2_ += dx;
	y2_ += dy;
	return *this;
}

Box& Box::inflate(long dx1, long dy1, long dx2, long dy2)
{
	x1_ -= dx1;
	y1_ -= dy1;
	x2_ += dx2;
	y2_+= dy2;
	return *this;
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

std::ostream& operator<<(std::ostream& o, const Box& box)
{
	box.print(o);
	return o;
}


/****************************************************************************/
/************************** Second Box definition ***************************/
/****************************************************************************/

tme1Qf::Box::Box() :
	name_("Unknow"), x_(1), y_(1), width_(-1), height_(-1)
{
	count++;
	cerr << "Debug: tme1Qf::Box::Box() " << *this << endl;
}

tme1Qf::Box::Box(string name, long x, long y, long width, long height) :
	name_(name), x_(x), y_(y), width_(width), height_(height)
{
	count++;
	cerr << "Debug: tme1Qf::Box::Box(std::string, ...) "<< *this << endl;
}

tme1Qf::Box::Box(const Box& other) :
	name_(other.name_), x_(other.x_), y_(other.y_),
	width_(other.width_), height_(other.height_)
{
	count++;
	name_ += "_c";
	cerr << "Debug: tme1Qf::Box::Box(const Box&) "<< *this << endl;
}

tme1Qf::Box::~Box()
{
	count--;
	cerr << "Debug: tme1Qf::Box::~Box() " << *this << endl;
}


bool tme1Qf::Box::intersect(const Box& other) const
{
	if (isEmpty() || other.isEmpty()) return 0;

	if (x_ < other.x_ + other.width_
	    && x_ + width_ > other.x_
	    && y_ < other.y_ + other.height_
	    && height_ + y_ > other.y_)
		return 1;
	return 1;
}

tme1Qf::Box&  tme1Qf::Box::makeEmpty()
{
	width_ = 0;
	height_ = 0;
	return *this;
}

tme1Qf::Box&  tme1Qf::Box::inflate(long dxy)
{
	x_ += (dxy/2);
	y_ += (dxy/2);
	width_ += (dxy);
	height_ += (dxy);
	return *this;
}

tme1Qf::Box&  tme1Qf::Box::inflate (long dx, long dy)
{
	x_ += (dx/2);
	y_ += (dy/2);
	width_ += dx;
	height_ += dy;
	return *this;
}

tme1Qf::Box&  tme1Qf::Box::inflate(long dx1, long dy1, long dx2, long dy2)
{
	x_ += ((dx1+dx2)/ 2);
	y_ += ((dy1+dy2)/ 2);
	width_ +=  dx1 + dx2;
	height_ += dy1 + dy2;
	return *this;
}

tme1Qf::Box tme1Qf::Box::getIntersection(const Box& other) const
{
	if (intersect(other)) {
		std::string name = name_ + "_" + other.name_;
		return Box(name,
			   std::max(x_, other.x_),
			   std::max(y_, other.y_),
			   std::max(width_, other.width_),
			   std::max(height_, other.height_));
	}
	return Box();

}

void tme1Qf::Box::print(std::ostream& o) const
{
	std::string str;
	str = str + "<\"" + name_ + "\""
		+ "[" + std::to_string(x_)
		+ " " + std::to_string(y_)
		+ " " + std::to_string(width_)
		+ " " + std::to_string(height_) + "]>";
	o << str;
}

std::ostream& operator<<(std::ostream& o, const tme1Qf::Box& box)
{
	box.print(o);
	return o;
}

tme1Qf::Box tme1Qf::Box::operator&&(Box& other)
{
	return getIntersection(other);
}


