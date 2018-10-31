#include "Shape/definition/LineShape.h"
#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"
#include <libxml/xmlreader.h>


namespace Netlist
{

LineShape::LineShape(Symbol* owner, int x1, int y1,int x2, int y2)
	:Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{

}

LineShape::~LineShape()
{

}



//LineShape* LineShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
//{
	//return NULL;
//}

//void BoxShape::toXml(std::ostream& o)
//{
	//o << indent << "<line x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
		//<< "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
//}

}
