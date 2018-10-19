#ifndef  NETLIST_INSTANCE_H
#define  NETLIST_INSTANCE_H

#include <string>
#include <vector>
using namespace std;

#include "Point.h"

namespace Netlist
{

class Term;
class Cell;
class Net;

class Instance{
private:
	Cell* owner_;
	Cell* masterCell_;
	string name_;
	vector<Term*> terms_;
	Point position_;
public:


	// Constructeurs & Destructeur. Ils devront gérer l'ajout et
	// le retrait de l'Instance au niveau de la Cell. Le constructeur
	// devra dupliquer la liste des terminaux de la Cell model
	// qu'il instancie. A l'inverse, le destructeur détruit ses terminaux.
	Instance(Cell* owner, Cell* model, const string&);


	// Une Instance possède ses terminaux, elle doit donc les
	// détruire dans son destructeur.
	~Instance();

	// getters
	const string& getName() const;
	Cell* getMasterCell() const;
	Cell* getCell() const;
	const vector<Term*>& getTerms() const;
	Term* getTerm(const string&) const;
	Point getPosition() const;

	//setters

	// Modificateurs. connect() va associer le Net
	// au terminal de nom name (s'il existe).
	bool connect( const string& name, Net* net);
	void add(Term*);
	void remove(Term*);
	void setPosition(const Point&);
	void setPosition(int x, int y);


	void toXml(ostream& o);
};

}
#endif //  NETLIST_INDENTATION_H
