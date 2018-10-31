#include "Shape/definition/TermShape.h"
#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"
#include <libxml/xmlreader.h>


namespace Netlist
{

TermShape::TermShape( Symbol* owner , string  name , int x1, int y1 )
	:Shape(owner), term_(NULL), x1_(x1), y1_(y1), align_(TermShape::TopLeft)
{
	//Cell* cell = getCell();
	//term_ = cell->getTerm(name);
}

TermShape::~TermShape()
{

}

//void setNameAlign(NameAlign align)
//{
	//align_ = align;
//}

//TermShape* TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
//{
	//return NULL;
//}

//void TermShape::toXml(std::ostream& o)
//{
	//o << indent << "<term name=\"" << this.term_->getName
		//<< "\" x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
		//<< "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
//}

}
