#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"
#include "Xml/XmlUtil.h"

namespace Netlist
{
class Symbol;

class  BoxShape2 : public Shape {
private:
	Box box_;

public:
	BoxShape2(Symbol*, const  Box&);
	BoxShape2(Symbol*, int x1 , int y1, int x2, int y2);
	virtual ~BoxShape2();
	virtual Box getBoundingBox() const;
	virtual void toXml(std::ostream& stream) const;
	static BoxShape2* fromXml(Symbol* owner, xmlTextReaderPtr reader);
};
}
#endif
