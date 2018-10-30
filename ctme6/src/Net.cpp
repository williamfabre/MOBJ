#include  <cstdlib>
//#include <libxml/xmlreader.h>
#include <fstream>

#include "Net.h"
#include "Cell.h"
#include "Node.h"
#include  "XmlUtil.h"

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
	return owner_;
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
	if (node){
		size_t id = node->getId();
		if ((id < nodes_.size()) and (nodes_[id]->getId()==id)){
			nodes_[id] = NULL;
			return true;
		}
	}
	return false;
}


void Net::toXml(ostream& o)
{
	vector<Node*>::const_iterator it = nodes_.begin();
	vector<Node*>::const_iterator end = nodes_.end();

	o << indent++ << "<net name=\"" << name_ << "\"";
	o << " type=\"" << Term::toString(type_) << "\">";
	o << endl;
	for (; it != end; it++)
		(*it)->toXml(o);
	o << --indent << "</net>";
	o << endl;
}

Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader)
{
	Net* net = NULL;
	string unexpected;
	const xmlChar* nodeTag;
	const xmlChar* nodeName;


	string s_name;
	string s_type;

	xmlChar* xml_name_value;
	xmlChar* xml_type_value;

	const xmlChar* xml_name;
	const xmlChar* xml_type;

	// s'il y a declaration d'un name
	xml_name = (const xmlChar*)"name";
	xml_type = (const xmlChar*)"type";

	// prendre la valeur de la declaration
	xml_name_value = xmlTextReaderGetAttribute(reader, xml_name);
	xml_type_value= xmlTextReaderGetAttribute(reader, xml_type);

	// transformer cette valeur en string
	s_name = xmlCharToString(xml_name_value);
	s_type = xmlCharToString(xml_type_value);

	if (not (s_name.empty() && s_type.empty())) {
		net = new Net(cell, s_name, Term::toType(s_type));
	} else {
		return NULL;
	}

	///////////// BEGIN PARSING des NODES /////////////////

	nodeName = xmlTextReaderConstLocalName(reader);
	nodeTag = xmlTextReaderConstString(reader, (const xmlChar*)"node");
	unexpected = "[ERR] Cell::fromXml(): Unexpected termination of parser.";

	//if (nodeTag != nodeName || !isEnd(reader))
		//return net;

	while(nodeTag == nodeName || !isEnd(reader)){
		int status = xmlTextReaderRead(reader);
		if (status != 1) {
			if (status != 0) {
				cerr << unexpected;
				cerr << endl;
			}
			break;
		}

		// On elimine les commentaires, espaces et tabs
		switch (xmlTextReaderNodeType(reader)) {
		case XML_READER_TYPE_COMMENT:
		case XML_READER_TYPE_WHITESPACE:
		case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
			continue;
		}

		//const xmlChar* tmpnodeName = xmlTextReaderConstLocalName     ( reader );
		nodeName = xmlTextReaderConstLocalName(reader);
		//if (nodeName == nodeTag){
			if (!(Node::fromXml(net ,reader))) break;
		//}
	}
	///////////// END PARSING des NODES /////////////////

	return net;
}

}
