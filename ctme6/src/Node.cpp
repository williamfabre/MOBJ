#include  <limits>

#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"
#include "XmlUtil.h"

namespace Netlist {


// id du node
const size_t Node::noid = numeric_limits<size_t>::max();

Node::Node(Term* term, size_t id) : id_(noid), term_(term), position_()
{
		id_ = id;
}


Node::~Node ()
{
	if (getNet())
		getNet()->remove(this);
}


inline Net* Node::getNet() const {return term_->getNet();}


// Node::toXml() à écrire ici.
void Node::toXml(ostream& o)
{
	o << indent << "<node term=\"" << term_->getName() << "\"";
	if (term_->isInternal())
		o << " instance=\"" << term_->getInstance()->getName() << "\"";
	o << " id=\"" << id_ << "\"";
	o << " x=\"" << position_.getX() << "\"";
	o << " y=\"" << position_.getY() << "\"/>";
	o << endl;
}


bool Node::fromXml(Net* net, xmlTextReaderPtr reader)
{

	bool res = false;
	bool coord = false;
	int x, y;
	Cell* c;
	Instance * inst;

	string s_term;
	string s_instance;
	string s_id;
	string s_x;
	string s_y;

	xmlChar* xml_term_value;
	xmlChar* xml_instance_value;
	xmlChar* xml_id_value;
	xmlChar* xml_x_value;
	xmlChar* xml_y_value;

	const xmlChar* xml_term;
	const xmlChar* xml_instance;
	const xmlChar* xml_id;
	const xmlChar* xml_x;
	const xmlChar* xml_y;

	// s'il y a declaration d'un name
	xml_term = (const xmlChar*)"term";
	xml_instance = (const xmlChar*)"instance";
	xml_id = (const xmlChar*)"id";
	xml_x = (const xmlChar*)"x";
	xml_y = (const xmlChar*)"y";

	// prendre la valeur de la declaration
	xml_term_value = xmlTextReaderGetAttribute(reader, xml_term);
	xml_instance_value= xmlTextReaderGetAttribute(reader, xml_instance);
	xml_id_value= xmlTextReaderGetAttribute(reader, xml_id);
	xml_x_value = xmlTextReaderGetAttribute(reader, xml_x);
	xml_y_value = xmlTextReaderGetAttribute(reader, xml_y);

	// transformer cette valeur en string
	s_term= xmlCharToString(xml_term_value);
	s_instance = xmlCharToString(xml_instance_value);
	s_id = xmlCharToString(xml_id_value);
	s_x = xmlCharToString(xml_x_value);
	s_y = xmlCharToString(xml_y_value);

	if (s_term.empty() || s_id.empty()) {
		return false;
	}
	if (not (s_x.empty() || s_y.empty())){
		// nous possedons des coordonnes a utiliser.
		coord = true;
		x = atoi(s_x.c_str());
		y = atoi(s_y.c_str());
	}
	if (not (s_instance.empty())){
		// on gere quelque chose relie a une instance et non une cell
		inst = net->getCell()->getInstance(s_instance);
		res = inst->connect(s_term, net);
		if (coord)
			inst->getTerm(s_term)->setPosition(x, y);
	} else {
		// on gere quelque chose qui va relier sur une cell
		c = net->getCell();
		res = c->connect(s_term, net);
		if (coord)
			c->getTerm(s_term)->setPosition(x, y);
	}
	return res;
}

}  // Netlist namespace.
