#include <ostream>
#include "Symbol/Symbol.h"
#include "Shape/Shape.h"
#include "Shape/definition/TermShape.h"

namespace Netlist {

using namespace std;

Symbol::Symbol(Cell* cell)
{
	owner_ = cell;
}

// Constructeur par copie pour les shapes
Symbol::Symbol ( const Symbol& symbol)
	: owner_(symbol.getCell()), shapes_(symbol.getShapes())
{

}

Symbol::~Symbol()
{
	// TODO
}

Cell* Symbol::getCell() const
{
	return owner_;
}

Box Symbol::getBoundingBox() const
{
	Box bb;
	vector<Shape*>::const_iterator ishape = shapes_.begin();
	for ( ;ishape != shapes_.end(); ++ishape){
		bb.merge((*ishape)->getBoundingBox());
	}
	return bb;
}

const TermShape* Symbol::getTermShape(Term* term) const
{
	const TermShape* ts;
	vector<Shape*>::const_iterator ishape = shapes_.begin();
	for ( ;ishape != shapes_.end(); ++ishape){
		// Check si c'est un term shape et si c'est le bon term shape
		ts = dynamic_cast<TermShape*>(*ishape);
		if (ts != NULL && ts->getTerm() == term)
			return ts;
	}
	return NULL;
}


Point Symbol::getTermPosition(Term* term) const
{
	int x, y;
	const TermShape* ts;
	ts = getTermShape(term);
	if (!ts){
		x = ts->getX();
		y = ts->getY();
		return Point(x,y);
	}
}

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

void Symbol::toXml(ostream& stream) const
{
	vector<Shape*>::const_iterator ishape = shapes_.begin();

	stream << indent++ << "<symbol>" << endl;
	for ( ;ishape != shapes_.end(); ishape++)
		(*ishape)->toXml(stream);
	stream << --indent << "</symbol>" << endl;
}

Symbol* Symbol::fromXml( Cell*, xmlTextReaderPtr )
{
	// TODO
	return NULL;
}


Symbol& Symbol::operator=( const Symbol& )
{
	// TODO
}


}

