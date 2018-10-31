#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"

namespace Netlist
{
class Symbol;
class Shape;
class Box;

class  BoxShape : public Shape {
private:
	Box box_;

public:
	BoxShape(Symbol*, const  Box&);
	BoxShape(Symbol*, int x1 , int y1, int x2, int y2);
	~BoxShape();
	Box getBoundingBox()  const;
	//BoxShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
	//void toXml(std::ostream&);
};
}
#endif
