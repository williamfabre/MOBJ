#include "Net.h"
#include "Cell.h"
#include "Node.h"

namespace Netlist {

Net::Net(Cell* cell, const std::string& str, Term::Type t)
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
	return NULL;
}

unsigned int Net::getId() const
{
	return 0;
}

Term::Type Net::getType() const
{
	return Term::Type::External;
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
