#ifndef NETLIST_CELL_H
#define NETLIST_CELL_H

#include <iostream>
#include <string>
#include <vector>
#include "Indentation.h"

namespace Netlist {

class Instance;
class Net;
class Term;


class Cell {
private:
	static std::vector<Cell*> cells_;
	std::string             name_;
	std::vector<Term*>      terms_;
	std::vector<Instance*>  instances_;
	std::vector<Net*>       nets_;
	unsigned int            maxNetIds_;

public:
	static std::vector<Cell*>& getAllCells();
	static Cell* find( const std::string& );

public:
	Cell(const std::string&);
	~Cell();

	// Getters
	inline const std::string& getName() const
	{return name_;};
	inline const std::vector<Instance*>& getInstances() const
	{return instances_;}
	inline const std::vector<Term*>& getTerms() const
	{return terms_;}
	inline const std::vector<Net*>& getNets() const
	{return nets_;}
	Instance* getInstance(const std::string&) const;
	Term* getTerm(const std::string&) const;
	Net* getNet(const std::string&) const;

	// Setters
	void setName(const std::string&);
	void add(Instance*);
	void add(Term*);
	void add(Net*);
	void remove(Instance*);
	void remove(Term*);
	void remove(Net*);
	bool connect(const std::string& name, Net* net );
	unsigned int newNetId();

	void toXml(std::ostream& stream);
};
}  // Netlist namespace.

#endif  // NETLIST_CELL_H

