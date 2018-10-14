#include "Instance.h"
#include "Cell.h"
#include "Term.h"

namespace Netlist {

Instance::Instance(Cell* owner, Cell* model, const std::string& str)
{

}
Instance::~Instance()
{

}

// getters
const std::string& Instance::getName() const
{
	return NULL;
}
Cell* Instance::getMasterCell() const
{
	return NULL;
}
Cell* Instance::getCell() const
{
	return NULL;
}
const std::vector<Term*>& Instance::getTerms() const
{
	return terms_;
}
Term* Instance::getTerm(const std::string&) const
{
	return *(terms_.begin());
}
Point Instance::getPosition() const
{
	return position_;
}

//setters
bool Instance::connect( const std::string& name, Net* net)
{
	return false;
}
void Instance::add(Term*)
{

}
void Instance::remove(Term*)
{

}
void Instance::setPosition(const Point&)
{

}
void Instance::setPosition(int x, int y)
{

}

}
