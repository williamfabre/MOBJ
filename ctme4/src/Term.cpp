#include "Term.h"
#include "Cell.h"
#include "Instance.h"

namespace Netlist {

using namespace std;

Term::Term(Cell* ce, const std::string& name, Term::Direction d) :
owner_((void*)ce), name_(name), direction_(d), net_(NULL), node_(this, 0)
{
	// TODO
}

Term::Term(Instance* in, const Term* modelTerm) :
owner_((void*)in), name_(modelTerm->getName()),
	direction_(modelTerm->getDirection()), net_(NULL), node_(this, 0)
{
	// TODO
}

Term::~Term()
{

}
/////////////////////////////
std::string Term::toString(Term::Type typ)
{
	return "Internal";
}

std::string Term::toString(Term::Direction dir)
{
	return "Unknown";
}

Term::Direction Term::toDirection(std::string str)
{
	return Unknown;
}

Cell* Term::getOwnerCell() const
{
	(type_ == External) ? static_cast<Cell*>(owner_)
		: static_cast<Instance*>(owner_);

}

void Term::setNet(Net* net)
{
	net_ = net;
}

void Term::setNet(const std::string& str)
{

}
void Term::setPosition(const Point& pt)
{

}

void Term::setPosition(int x, int y)
{

}

}
