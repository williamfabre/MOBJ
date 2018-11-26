#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape/Shape.h"
#include "Box/Box.h"

namespace Netlist
{
class Symbol;

class TermShape : public  Shape {

public:
	enum NameAlign { TopLeft=1, TopRight=2, BottomLeft, BottomRight };
private:
	Term* term_;
	int x1_, y1_;
	NameAlign align_;

public:
	/* x, y centre du term */
	TermShape( Symbol*, string  name , int x, int y );
	virtual ~TermShape();
	virtual Box getBoundingBox() const
	{
		return Box(x1_, y1_,x1_, y1_);
	}
	void setNameAlign(NameAlign align);
	inline Term* getTerm() const {return term_;}
	inline int getX() const {return x1_;}
	inline int getY() const {return y1_;}

	virtual void toXml(std::ostream&);
	static TermShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);

	std::string a2s(NameAlign align);
	NameAlign s2a(std::string align);
};
}
#endif
