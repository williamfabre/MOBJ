#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Box/Box.h"
#include "Xml/XmlUtil.h"
#include "Shape/Shape.h"

namespace Netlist
{
class Symbol;
class Term;

class TermShape : public  Shape
{
	enum NameAlign { TopLeft=1, TopRight=2, BottomLeft=3, BottomRight=4 };
private:
	Term* term_;
	//x, y centre du term
	int x1_, y1_;
	NameAlign align_;

public:
	static TermShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
	static string a2s(NameAlign align);
	static NameAlign s2a(string align);
	TermShape(Symbol* owner, string  name , int x, int y);
	virtual ~TermShape();
	virtual Box getBoundingBox() const;

	void setNameAlign(NameAlign align);
	inline Term* getTerm() const {return term_;}
	inline int getX() const {return x1_;}
	inline int getY() const {return y1_;}

	virtual void toXml(std::ostream& stream) const;
};
}
#endif
