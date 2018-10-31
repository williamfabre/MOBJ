#include <cstdlib>
#include "Symbol/Symbol.h"
#include "Shape/Shape.h"

namespace Netlist
{

Shape::Shape(Symbol* owner) : owner_(owner)
{
	owner_->add(this);
}

Shape::~Shape()
{
	owner_->remove(this);
}
}
