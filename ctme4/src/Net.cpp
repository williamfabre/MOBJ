#include "Net.h"
#include "Cell.h"
#include "Node.h"

namespace Netlist {

Net::Net(Cell* cell, const std::string& str, Term::Type t)
//owner_(c), name_(s), id_(owner_->newNetId()), type_(t), nodes_()

{

}

Net::~Net()
{

}

using namespace std;

Cell* Net::getCell() const
{
	return NULL;
}

const std::string& Net::getName() const
{
	return name_;
}

unsigned int Net::getId() const
{
	return 0;
}

Term::Type Net::getType() const
{
	return type_;
}

const std::vector<Node*>& Net::getNodes() const
{
	return this->nodes_;
}

size_t Net::getFreeNodeId() const
{
	return 0;
}

//setters
void Net::add(Node* node)
{
}

bool Net::remove(Node* node)
{
	return 0;
}

}
