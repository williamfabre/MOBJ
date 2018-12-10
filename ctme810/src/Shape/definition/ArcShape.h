#ifndef NETLIST_ARCSHAPE_H
#define NETLIST_ARCSHAPE_H

#include "Shape/Shape.h"
#include "Xml/XmlUtil.h"
#include "Box/Box.h"

namespace Netlist {

class Symbol;

class ArcShape : public Shape {
private:
	Box box_;
	int start_;
	int span_;
public:
	static ArcShape* fromXml(Symbol*, xmlTextReaderPtr);
	ArcShape(Symbol* owner, const Box& box, int start, int span);
	ArcShape(Symbol* owner, int x1, int y1, int x2, int y2,
			int start, int span);
	inline int getStart()
	{
		return start_;
	}
	inline int getSpan()
	{
		return span_;
	}
	~ArcShape ();
	Box getBoundingBox() const;
	void toXml (std::ostream&) const;
};
}

#endif
