#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"

namespace Netlist
{
class Symbol;

class  TermShape : public  Shape {
	enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };
public:
	TermShape( Symbol*, string  name , int x, int y );
	~TermShape();
	//Box getBoundingBox() const;
	Box getBoundingBox() const
	{
		return Box(x1_, y1_,x1_, y1_);
	}

	//void setNameAlign(NameAlign align);

	inline Term* getTerm() const {return term_;}

	inline int getX() const {return x1_;}

	inline int getY() const {return y1_;}

	//TermShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
	//void toXml(std::ostream&);
private:
	Term* term_;
	int x1_, y1_;
	NameAlign align_;
};
}
#endif
