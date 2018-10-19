#include "Net.h"
#include "Cell.h"
#include "Node.h"

namespace Netlist {

Net::Net(Cell* cell, const string& str, Term::Type t) :
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


Cell* Net::getCell() const
{
	return (type_ == Term::External) ? owner_ : NULL;
}

const string& Net::getName() const
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

const vector<Node*>& Net::getNodes() const
{
	return nodes_;
}

size_t Net::getFreeNodeId() const
{
	vector<Node*>::const_iterator it = nodes_.begin();
	vector<Node*>::const_iterator end = nodes_.end();
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
	if (node->getId() == Node::noid){
		nodes_.insert(nodes_.begin() + index, node);
		node->setId(index);
	} else {
		// TODO attention insert meme s'il y a deja quelqu'un
		nodes_.insert(nodes_.begin() + node->getId(), node);
	}

}


bool Net::remove(Node* node)
{
	vector<Node*>::iterator it = nodes_.begin();
	vector<Node*>::iterator end = nodes_.end();

	for ( ;it != end ; it++){
		if ((*it) == node){
			(*it) = NULL;
			break;
		}
	}

	return (*it) == NULL;
}


void Net::toXml(ostream& o)
{
	vector<Node*>::const_iterator it = nodes_.begin();
	vector<Node*>::const_iterator end = nodes_.end();

	o << indent++ << "<net name=\"" << name_ << "\"";
	o << " type=\"" << Term::toString(type_) << "\"/>";
	o << endl;
	for (; it != end; it++)
		(*it)->toXml(o);
	o << --indent << "</net>";
	o << endl;
}

}
