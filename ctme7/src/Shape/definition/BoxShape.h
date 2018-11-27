#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"

namespace Netlist
{
class Symbol;

class  BoxShape : public Shape {
private:
	Box box_;

public:
	BoxShape(Symbol*, const  Box&);
	BoxShape(Symbol*, int x1 , int y1, int x2, int y2);
	virtual ~BoxShape();
	virtual Box getBoundingBox() const;
	virtual void toXml(std::ostream& stream) const;
	static BoxShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
};
}
#endif
