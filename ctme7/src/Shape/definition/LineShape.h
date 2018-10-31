#ifndef NETLIST_LINESHAPE_H
#define NETLIST_LINESHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"

namespace Netlist
{
class Symbol;

class LineShape : public Shape
	{
	private:
		int x1_, y1_, x2_, y2_;

	public:
		LineShape(Symbol*, int x1, int y1, int x2, int y2);
		~LineShape();
		//Box getBoundingBox() const;
		// Need to be done into the class because virtual
		Box getBoundingBox() const
		{
			return Box(x1_, y1_, x2_, y2_);
		}

		inline int getX1() const {return x1_;}
		inline int getY1() const {return y1_;}
		inline int getX2() const {return x2_;}
		inline int getY2() const {return y2_;}
		//LineShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
		//void toXml(std::ostream&);
	};
}
#endif
