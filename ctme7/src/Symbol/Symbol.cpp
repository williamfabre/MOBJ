#include  "Xml/XmlUtil.h"
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
		(*ishape)->toXml(stream);
	stream << --indent << "</symbol>" << endl;
}

Symbol* Symbol::fromXml( Cell* owner, xmlTextReaderPtr reader)
{

	enum State { endSymbol };
	const xmlChar*    symbolTag;
	const xmlChar*    boxTag;
	const xmlChar*    lineTag;
	const xmlChar*    termTag;
	const xmlChar*    ellipseTag;
	const xmlChar*    arcTag;
	const xmlChar*    nodeName;
	int               nodeType;
	Symbol*           symbol;
	State		          state;

	symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );
	boxTag = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
	lineTag = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
	termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
	ellipseTag = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
	arcTag = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
	nodeName = xmlTextReaderConstLocalName(reader);
	nodeType = xmlTextReaderNodeType(reader);

	// if (line == "<symbol>")
	if (nodeName == symbolTag && nodeType == XML_READER_TYPE_ELEMENT)
	{
		state = endSymbol;

		// Retrieving the Symbol to set
		symbol = owner->getSymbol(); 

		// Read all Node
		while (true) {
			int status = xmlTextReaderRead(reader);
			// If reached EOF or current line is incorrect, exit failure
			if (status != 1) {
				std::cerr << "[ERROR] Net::fromXml(): "
					<< "Unexpected termination of the XML parser."
					<< std::endl;
				break;
			}

			// Pass comments and blank lines
			switch ( xmlTextReaderNodeType(reader) ) {
			case XML_READER_TYPE_COMMENT:
			case XML_READER_TYPE_WHITESPACE:
			case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
				continue;
			}

			nodeName = xmlTextReaderConstLocalName(reader);
			nodeType = xmlTextReaderNodeType(reader);

			//std::cerr << "nodeName: " << xmlCharToString(nodeName) << std::endl;
			std::cerr << "nodeType: " << nodeType << std::endl;

			switch (state) {
			case endSymbol:
				// if line == </symbol>, finish reading correctly (return true)
				if ((nodeName == symbolTag) and
				    (xmlTextReaderNodeType(reader)
				     == XML_READER_TYPE_END_ELEMENT)) { 
					return symbol; // finished reading, successfully
				}
				// if line == <someshape... />
				else if ((nodeName == boxTag
					  or nodeName == lineTag
					  or nodeName == termTag
					  or nodeName == ellipseTag
					  or nodeName == arcTag)
					 and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)) {
					if (Shape::fromXml(symbol, reader)) continue;
				}
				else
					std::cerr << "No shape tag" << std::endl;
				// if line is incorrect, break
				break;
			default:
				break;
			} // end of switch
			// if any error occured, return incorrectly (return NULL)
			std::cerr << "[ERROR] Net::fromXml(): Unknown or misplaced tag <"
				<< nodeName << "<"
				<< "(line: " << xmlTextReaderGetParserLineNumber(reader)
				<< ")." << std::endl;
			break;
		}
	} // end of while
	return NULL; // reading ended in failure
}


//Symbol& Symbol::operator=(const Symbol& sym) const
//{
//}


}

