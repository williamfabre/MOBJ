#include  <cstdlib>
//#include <libxml/xmlreader.h>
#include <fstream>

#include "Net/Net.h"
#include "Cell/Cell.h"
#include "Node/Node.h"
#include "Xml/XmlUtil.h"
#include "Line/Line.h"

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

Node* Net::getNode(int index)
{
	return nodes_.at(index);
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
				//cerr << "case pleine" << endl;
				//cerr << nodes_[id]->getPosition() <<endl;
				//nodes_[id]->setId(Node::noid);
				//for (vector<Node*>::const_iterator it = nodes_.begin();
				     //it < nodes_.end(); it++)
					//cerr << (*it)->getId() << " " ;
				//nodes_[id]->setId(getFreeNodeId());
				// GESTION d'erreur
				return;
			}
			nodes_[id] = node; // positionne l'id
			return;
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

void  Net::add ( Line* line )
{
	if (line) lines_.push_back( line );
}

bool  Net::remove ( Line* line )
{
	if (line) {
		for ( vector<Line*>::iterator il = lines_.begin()
		      ; il != lines_.end() ; ++il ) {
			if (*il == line) {
				lines_.erase( il );
				return true;
			}
		}
	}
	return false;
}


// TODO MODIFIER AVEC TME7
void Net::toXml(ostream& o)
{
	vector<Node*>::const_iterator itnode = nodes_.begin();
	vector<Node*>::const_iterator endnode = nodes_.end();

	vector<Line*>::const_iterator itline = lines_.begin();
	vector<Line*>::const_iterator endline = lines_.end();

	o << indent++ << "<net name=\"" << name_ << "\"";
	o << " type=\"" << Term::toString(type_) << "\">";
	o << endl;
	for (; itnode != endnode; itnode++){
		if (*itnode)
			(*itnode)->toXml(o);
	}
	for (; itline != endline; itline++){
		if (*itline)
			(*itline)->toXml(o);
	}
	o << --indent << "</net>";
	o << endl;
}

// TODO MODIFIER AVEC TME7
Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader)
{
	Net* net = NULL;
	string unexpected;
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
	unexpected = "[ERR] Net::fromXml(): Unexpected termination of parser.";

	while(!isEnd(reader)){
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

		nodeName = xmlTextReaderConstLocalName(reader);
		const xmlChar* NodeTag
			= xmlTextReaderConstString( reader, (const xmlChar*)"node");
		const xmlChar* LineTag
			= xmlTextReaderConstString( reader, (const xmlChar*)"line");

		if (NodeTag == nodeName){
			if ((Node::fromXml(net ,reader))) continue;
		}
		if (LineTag == nodeName){
			if ((Line::fromXml(net ,reader))) continue;
		}
	}
	return net;
///////////// END PARSING des NODES /////////////////
}
}
