
#ifndef NETLIST_ELLIPSESHAPE_H
#define NETLIST_ELLIPSESHAPE_H

#include "Shape/Shape.h"

namespace Netlist {

class Shape;
class Symbol;

class EllipseShape : public Shape {
private:
	Box box_;
public:
	static EllipseShape* fromXml(Symbol*, xmlTextReaderPtr);
	EllipseShape(Symbol* owner, const Box& box);
	EllipseShape(Symbol* owner, int x1, int y1, int x2, int y2);
	~EllipseShape();
	Box getBoundingBox() const;
	void toXml(std::ostream&) const;
};
}

#endif
