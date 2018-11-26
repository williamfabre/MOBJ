#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"
#include <libxml/xmlreader.h>
#include "Shape/definition/LineShape.h"


namespace Netlist
{

LineShape::LineShape(Symbol* owner, int x1, int y1,int x2, int y2)
	:Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{
}

LineShape::~LineShape()
{

}


Box LineShape::getBoundingBox () const
{
	return Box(min(x1_, x2_),
		   min(y1_, y2_),
		   max(x1_, x2_),
		   max(y1_, y2_));
}

LineShape* LineShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
	return NULL;
}

void LineShape::toXml(std::ostream& o)
{
}

}
