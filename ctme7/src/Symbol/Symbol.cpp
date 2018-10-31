#include <ostream>
#include "Symbol/Symbol.h"

namespace Netlist {

using namespace std;

Symbol::Symbol(Cell* cell)
{
	owner_ = cell;
}

Symbol::~Symbol()
{
	// TODO
}

Cell* Symbol::getCell() const
{
	return owner_;
}

//Box Symbol::getBoundingBox() const
//{
//return NULL;
//}

//Point Symbol::getTermPosition(Term*) const
//{
//return NULL;
//}

//TermShape* Symbol::getTermShape(Term*) const
//{
//return NULL;
//}

//inline const std::vector<Shape*> Symbol::getShapes() const
//{
//return NULL;
//}

void Symbol::add( Shape* shape)
{
	shapes_.push_back(shape);

}

void Symbol::remove(Shape* shape)
{
	for (vector<Shape*>::iterator ishape=shapes_.begin();
	      ishape != shapes_.end() ; ++ishape ) {
		if (*ishape == shape) shapes_.erase( ishape );
	}
}

void Symbol::toXml( std::ostream& ) const
{

}

//Symbol* Symbol::fromXml( Cell*, xmlTextReaderPtr )
//{
//
//}

//Symbol::Symbol ( const Symbol& )
//{
//return NULL;
//}

//Symbol& Symbol::operator=( const Symbol& )
//{
//return NULL;
//}


}

