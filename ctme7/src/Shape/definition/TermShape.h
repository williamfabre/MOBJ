#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Box/Box.h"

namespace Netlist
{
class Term;
class Box;

class TermShape : public  Shape
{
	enum NameAlign { TopLeft=1, TopRight=2, BottomLeft, BottomRight };
private:
	Term* term_;
	int x1_, y1_;
	NameAlign align_;

public:
	//x, y centre du term
	TermShape(Symbol*, string  name , int x, int y);

	static string a2s(NameAlign align);
	static NameAlign s2a(string align);

	virtual ~TermShape();
	virtual Box getBoundingBox() const;
	void setNameAlign(NameAlign align);
	inline Term* getTerm() const {return term_;}
	inline int getX() const {return x1_;}
	inline int getY() const {return y1_;}

	static TermShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
	virtual void toXml(std::ostream& stream) const;

};
}
#endif
