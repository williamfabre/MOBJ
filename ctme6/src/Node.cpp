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
	string s_term;
	string s_instance;
	string s_id;

	xmlChar* xml_term_value;
	xmlChar* xml_instance_value;
	xmlChar* xml_id_value;

	const xmlChar* xml_term;
	const xmlChar* xml_instance;
	const xmlChar* xml_id;

	// s'il y a declaration d'un name
	xml_term = (const xmlChar*)"term";
	xml_instance = (const xmlChar*)"instance";
	xml_id = (const xmlChar*)"id";

	// prendre la valeur de la declaration
	xml_term_value = xmlTextReaderGetAttribute(reader, xml_term);
	xml_instance_value= xmlTextReaderGetAttribute(reader, xml_instance);
	xml_id_value= xmlTextReaderGetAttribute(reader, xml_id);

	// transformer cette valeur en string
	s_term= xmlCharToString(xml_term_value);
	s_instance = xmlCharToString(xml_instance_value);
	s_id = xmlCharToString(xml_id_value);

	// Si le nom n'est pas vide alors on demande
	// la creation de la cellule
	if (not (s_term.empty() && s_id.empty())) {

		if (!s_instance.empty()){
			Cell* c = net->getCell();
			bool res;
			res = c->getInstance(s_instance)->connect(s_term, net);
			return !res;
		}
		bool res = net->getCell()->connect(s_term, net);
		return !res;
	}
	return false;

}

}  // Netlist namespace.
