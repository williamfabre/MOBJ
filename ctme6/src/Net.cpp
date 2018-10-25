#include <libxml/xmlreader.h>

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
//void Net::add(Node* node)
//{
	//// find space

	//// first case no id has been set
	//if (node->getId() == Node::noid){
		//size_t index = Net::getFreeNodeId();
		//nodes_.insert(nodes_.begin() + index, node);
		//node->setId(index);
		//if (id < nodes_.size()){

		//}
	//} else {
		//if (node_[id] != null){
			//cerr << "attention case pleine";
			//nodes_[id]->setId(Node::noid);
		//}
		//// TODO attention insert meme s'il y a deja quelqu'un
		//nodes_.insert(nodes_.begin() + node->getId(), node);
	//}

//}


void Net::add(Node* node)
{
	if (node){
		size_t id = node->getId();
		if (id == Node::noid){ // le noeud na pas d'id
			id = getFreeNodeId(); // found case libre
			node->setId(id); //positionne id valide
		}
		if (id < nodes_.size()){ // l'id est valide
			if (nodes_[id] != NULL){ // erreur
				cerr << "case pleine" << endl;
				nodes_[id]->setId(Node::noid);
				// GESTION d'erreur
				return;
			}
			nodes_[id] = node; // positionne l'id
		} else {
			// gestion du tableau trop petit
			for (size_t i = nodes_.size(); i < id; ++i){
				nodes_.push_back(NULL);
			}
		}
	}
	// on arrive a la case id cases vide -> case id
	nodes_.push_back(node);
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

Net* Net::fromXml(Cell* cell, _xmlTextReader* reader)
{
	return NULL;
}

}
