#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H

#include <string>
#include <vector>
#include "Term.h"

namespace Netlist
{

class Cell;
class Node;

class Net {
private:

	Cell* owner_;
	std::string name_;
	unsigned int id_;
	Term::Type type_;
	std::vector<Node*> nodes_;

public:
	Net(Cell* cell, const std::string& str, Term::Type t);
	~Net();

	// getters
	Cell* getCell() const;
	const std::string& getName() const;
	unsigned int getId() const;
	Term::Type getType() const;
	const std::vector<Node*>& getNodes() const;
	size_t getFreeNodeId() const;

	//setters
	void add(Node* node); // ajouter un node connecter a un autre truc
	bool remove(Node* node);

};

}
#endif //  NETLIST_INDENTATION_H
