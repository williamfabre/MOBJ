#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

//#include "Symbol/Symbol.h"
//#include "Box/Box.h"
#include "Cell/Cell.h"

namespace Netlist
{
class Box;
class Symbol;
class BoxShape;
class EllipseShape;
class ArcShape;
class LineShape;

class  Shape
{

private:
	Symbol* owner_;
public:
	Shape(Symbol* owner);
	virtual ~Shape();
	inline Cell* getCell() const {return owner_->getCell();}
	inline Symbol* getSymbol() const {return owner_;}
	virtual Box getBoundingBox() const = 0;
	/* getBoundingBox est surdefini et non surcharge dans les classes
	   derivees.
	   On utilise donc le mot cle virtual pour rendre la fonction
	   virtuelle. Si on appelle cette methode au travers d'un pointeur
	   ou d'une reference alors on appelle la methode de la classe
	   derivee (= l'objet reel).
	   ceci est propage aux classes derivees donc on est pas oblige de
	   mettre le mot cle mais pour des raisons de clareter LE FAIRE
	   Le prototype d'une fonction surdefini doit etre identique.
	   signature + type de retour (ceci n'est pas forcement vraie on peut
	   s'amuser a faire des appel en cascade avec un autre type et un autre
	   retour.
	   le = 0 veut dire aucune definition dans la classe de base, on appelle
	   ca une fonction virtuelle pure.
	   Tout classe possedant au moins une fonction virtuelle pure est dite
	   ABSTRAITE
	   vtable object -> definition virtuelle pure
	   */
	virtual void toXml(std::ostream& stream) const = 0;
	static Shape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
};

}
#endif
