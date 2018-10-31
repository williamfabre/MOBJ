#include "Shape/definition/BoxShape.h"
#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"
#include <libxml/xmlreader.h>

namespace Netlist
{

BoxShape::BoxShape(Symbol* owner, const Box& box)
	:Shape(owner), box_(box)
{

}

BoxShape::BoxShape(Symbol* owner, int x1 , int y1, int x2, int y2)
	:Shape(owner),box_(x1,y1,x2,y2)
{

}

BoxShape::~BoxShape()
{

}

Box BoxShape::getBoundingBox() const
{
	return box_;
}

//BoxShape* BoxShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
//{
	//return NULL;
//}

//void BoxShape::toXml(std::ostream& o)
//{
	//o << indent << "<box x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
		//<< "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
//}

}
