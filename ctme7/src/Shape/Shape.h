#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "Symbol/Symbol.h"
#include "Box/Box.h"

namespace Netlist
{

class  Shape
{
private:
	Symbol* owner_;
public:
	Shape(Symbol*);
	virtual ~Shape();
	inline Symbol* getSymbol() const {return owner_;}
	virtual Box getBoundingBox() const = 0;
};

}
#endif
