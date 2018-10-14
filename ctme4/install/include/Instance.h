#ifndef  NETLIST_INSTANCE_H
#define  NETLIST_INSTANCE_H

#include <string>
#include <vector>
#include "Point.h"
//#include "Cell.h"

namespace Netlist
{

class Term;
class Cell;
class Net;

class Instance{
private:
	Cell* owner_;
	Cell* masterCell_;
	std::string name_;
	std::vector<Term*> terms_;
	Point position_;
public:

	Instance(Cell* owner, Cell* model, const std::string&);
	~Instance();

	// getters
	const std::string& getName() const;
	Cell* getMasterCell() const;
	Cell* getCell() const;
	const std::vector<Term*>& getTerms() const;
	Term* getTerm(const std::string&) const;
	Point getPosition() const;

	//setters
	bool connect( const std::string& name, Net* net);
	void add(Term*);
	void remove(Term*);
	void setPosition(const Point&);
	void setPosition(int x, int y);
};

}
#endif //  NETLIST_INDENTATION_H
