#include  "Xml/XmlUtil.h"
#include "Symbol/Symbol.h"
#include "Shape/Shape.h"
#include "Shape/definition/TermShape.h"
#include <ostream>

namespace Netlist {

using namespace std;

Symbol::Symbol(Cell* cell)
{
	owner_ = cell;
}

// Constructeur par copie pour les shapes
Symbol::Symbol (const Symbol& symbol)
	: owner_(symbol.getCell()), shapes_(symbol.getShapes())
{

}

Symbol::~Symbol()
{
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
	//if (!ts){
		x = ts->getX();
		y = ts->getY();
		return Point(x,y);
	//}
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
		if (*ishape)
			(*ishape)->toXml(stream);
	stream << --indent << "</symbol>" << endl;
}


Symbol* Symbol::fromXml(Cell* owner, xmlTextReaderPtr reader)
{
	string unexpected;
	const xmlChar* nodeTag;
	Shape* shape = NULL;
	const xmlChar* nodeName;
	Symbol* symbol = owner->getSymbol();

	///////////// begin parsing des nodes /////////////////
	nodeName = xmlTextReaderConstLocalName(reader);
	nodeTag=xmlTextReaderConstString(reader,(const xmlChar*)"symbol");
	unexpected="[err] Symbol::fromxml(): unexpected of parser.";

	while(!isEnd(reader)){

		int status = xmlTextReaderRead(reader);
		if (status != 1) {
			if (status != 0) {
				cerr << unexpected;
				cerr << endl;
			}
			break;
		}
		nodeName = xmlTextReaderConstLocalName(reader);
		if(nodeTag == nodeName){break;}

		// on elimine les commentaires, espaces et tabs
		switch (xmlTextReaderNodeType(reader)) {
		case XML_READER_TYPE_COMMENT:
		case XML_READER_TYPE_WHITESPACE:
		case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
			continue;
		}

		shape = Shape::fromXml(owner->getSymbol(), reader);

	}
	return symbol;
	/////////////// end parsing des nodes /////////////////
}

//Symbol* Symbol::fromXml(Cell* c, xmlTextReaderPtr reader){
	//const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"symbol" );
	//const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

	//Symbol* symbol = c->getSymbol();
	//Shape* shape = NULL;


	//while(true){
		////on fait avancer le pointeur
		//xmlTextReaderRead(reader);
		//nodeName = xmlTextReaderConstLocalName     ( reader );
		//if(nodeTag == nodeName){break;}

		//switch ( xmlTextReaderNodeType(reader) ) {
		//case XML_READER_TYPE_COMMENT:
		//case XML_READER_TYPE_WHITESPACE:
		//case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
			//continue;
		//}

		//shape->fromXml(symbol, reader);
		//if(shape) symbol->add(shape);
		////std::cout << "-----" << std::endl;
		////symbol->toXml(std::cout);

	//}
	//return symbol;
//}
// Techniquement c'est pour ne pas dupliquer
//Symbol& Symbol::operator=(const Symbol& sym) const
//{

//}


}

