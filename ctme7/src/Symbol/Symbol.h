// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_SYMBOL_H
#define NETLIST_SYMBOL_H

#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  "Box/Box.h"

namespace Netlist {

class Term;
class Cell;
class Shape;
class TermShape;


/* associe de maniere unique a une celle, son owner est la cell.
 * il possede un vecteur de touets les shapes. */
class Symbol {
private:
	Cell* owner_;
	std::vector<Shape*> shapes_;

public:
	Symbol(Cell*);
	~Symbol();
	Cell* getCell() const;
	/* donne la boite englobante de la cellule */
	Box getBoundingBox() const;
	Point getTermPosition(Term*) const;
	const TermShape* getTermShape(Term*) const;
	inline const std::vector<Shape*> getShapes() const {return shapes_;}
	void add(Shape*);
	void remove(Shape*);
	void toXml(std::ostream&) const;
	static Symbol* fromXml(Cell*, xmlTextReaderPtr);

private:
	Symbol (const Symbol&);
	Symbol& operator=(const Symbol&);
};
}  // Netlist namespace.

#endif  // NETLIST_SYMBOL_H
