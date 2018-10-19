#include "Net.h"
#include "Cell.h"
#include "Node.h"
//#include "Term.h"

namespace Netlist {

Net::Net(Cell* cell, const std::string& str, Term::Type t) :
	owner_(cell),
	name_(str),
	id_(owner_->newNetId()),
	type_(t),
	nodes_()
{
	owner_->add(this);
	//id_ = owner_->newNetId();
}

Net::~Net()
{
	owner_->remove(this);
}

using namespace std;

Cell* Net::getCell() const
{
	return (type_ == Term::External) ? owner_ : NULL;
}

const std::string& Net::getName() const
{
	return name_;
}

unsigned int Net::getId() const
{
	return id_;
}

Term::Type Net::getType() const
{
	return type_;
}

const std::vector<Node*>& Net::getNodes() const
{
	return nodes_;
}

size_t Net::getFreeNodeId() const
{
	std::vector<Node*>::const_iterator it = nodes_.begin();
	std::vector<Node*>::const_iterator end = nodes_.end();
	size_t i = 0;

	for (; it != end; it++)
		i++;

	if (i == nodes_.size() -1) i++;
	return i;
}

//setters
void Net::add(Node* node)
{
	// find space
	size_t index = Net::getFreeNodeId();

	// first case no id has been set
	if (node->getId() == Node::noid)
		nodes_.insert(nodes_.begin() + index, node);
	else
		nodes_.insert(nodes_.begin() + node->getId(), node);

	node->setId(index);

}

bool Net::remove(Node* node)
{

	std::vector<Node*>::iterator it = nodes_.begin();
	std::vector<Node*>::iterator end = nodes_.end();
	for ( ;it != end ; it++)
	{
		if ((*it) == node){
			(*it) = NULL;
			break;
		}
	}

	return (*it) == NULL;
}


void Net::toXml(std::ostream& o)
{
	std::vector<Node*>::const_iterator it = nodes_.begin();
	std::vector<Node*>::const_iterator end = nodes_.end();

	o << indent++ << "<net name=\"" << name_ << "\"";
	o << " type=\"" << Term::toString(type_) << "\"/>";
	o << endl;
	for (; it != end; it++)
		(*it)->toXml(o);
	o << --indent << "</net>";
	o << endl;
}

}
