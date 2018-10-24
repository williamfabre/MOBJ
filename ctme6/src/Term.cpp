#include <libxml/xmlreader.h>
#include <iostream>

#include "Indentation.h"
#include "Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"
#include  "XmlUtil.h"

namespace Netlist {


Term::Term(Cell* ce, const string& name, Term::Direction d) :
	owner_((void*)ce),
	name_(name),
	direction_(d),
	type_(Term::External),
	net_(NULL),
	node_(this)
{
	static_cast<Cell*>(owner_)->add(this);
}

Term::Term(Instance* in, const Term* modelTerm) :
	owner_((void *)in),
	name_(modelTerm->getName()),
	direction_(modelTerm->getDirection()),
	type_(Term::Internal),
	net_(NULL),
	node_(this)
{
	static_cast<Instance*>(owner_)->add(this);
}

Term::~Term()
{
	// destrucion d node associee du node :
	delete &node_;

	if (type_ == Term::External)
		static_cast<Cell*>(owner_)->remove(this);
	else
		static_cast<Instance*>(owner_)->remove(this);

	// Lorsqu'un Term est détruit, si il est accroché à un Net,
	// il doit s'en déconnecter dans son destructeur.
	if ((net_))
		net_ = NULL;
}

string Term::toString(Term::Type type)
{
	if (type == Term::Internal)
		return "Internal";
	return "External";
}

string Term::toString(Term::Direction direction)
{
	string dir;

	switch (direction) {
		case Term::In :
			dir = "In";
			break;
		case Term::Out :
			dir = "Out";
			break;
		case Term::Inout :
			dir = "Inout";
			break;
		case Term::Tristate :
			dir = "Tristate";
			break;
		case Term::Transcv :
			dir = "Transcv";
			break;
		default :
			dir = "Unknown";
	}
	return dir;
}

Term::Direction Term::toDirection(string stri)
{
	Term::Direction dir;
	bool changed = false;

	if (stri == "In") {dir = Term::In; changed = true;}
	if (stri == "Out") {dir = Term::Out; changed = true;}
	if (stri == "Inout") {dir = Term::Inout; changed = true;}
	if (stri == "Tristate") {dir = Term::Tristate; changed = true;}
	if (stri == "Transcv") {dir = Term::Transcv; changed = true;}

	if (stri == "Unknown" || !changed)
		dir = Term::Unknown;

	return dir;
}


Cell* Term::getOwnerCell() const
{
	if (type_ == External)
		return static_cast<Cell*>(owner_);

	return static_cast<Instance*>(owner_)->getCell();
}


void Term::setNet(Net* net)
{
	if (!net)
		net->remove(&node_);
	else
		net->add(&node_);

	net_ = net;
}


void Term::setNet(const string& str)
{
	Term::setNet(static_cast<Cell*>(owner_)->getNet(str));
}


void Term::setPosition(const Point& pt)
{
	node_.setPosition(pt);
}


void Term::setPosition(int x, int y)
{
	node_.setPosition(x, y);
}

void Term::toXml(ostream& o)
{
	//string dir;
	o << indent << "<term name=\"" << name_ << "\"";
	o << " direction=\"" << Term::toString(direction_) << "\"/>";
	o << endl;
}


Term* Term::fromXml(Cell* cell, xmlTextReaderPtr reader)
{
	string s_name;
	string s_direction;
	string s_x;
	string s_y;

	xmlChar* xml_name_value;
	xmlChar* xml_direction_value;
	xmlChar* xml_x_value;
	xmlChar* xml_y_value;

	const xmlChar* xml_name;
	const xmlChar* xml_direction;
	const xmlChar* xml_x;
	const xmlChar* xml_y;

	// s'il y a declaration d'un name
	xml_name = (const xmlChar*)"name";
	xml_direction = (const xmlChar*)"direction";
	xml_x = (const xmlChar*)"x";
	xml_y = (const xmlChar*)"y";

	// prendre la valeur de la declaration
	xml_name_value = xmlTextReaderGetAttribute(reader, xml_name);
	xml_direction_value = xmlTextReaderGetAttribute(reader, xml_direction);
	xml_x_value = xmlTextReaderGetAttribute(reader, xml_x);
	xml_y_value = xmlTextReaderGetAttribute(reader, xml_y);

	// transformer cette valeur en string
	s_name = xmlCharToString(xml_name_value);
	s_direction = xmlCharToString(xml_direction_value);
	s_x = xmlCharToString(xml_x_value);
	s_y = xmlCharToString(xml_y_value);

	// Si le nom n'est pas vide alors on demande
	// la creation de la cellule
	if (not (s_name.empty() && s_direction.empty() && s_x.empty()
		 && s_y.empty())) {
		// TODO GESTION DE X ET Y?
		Term* t = new Term(cell, s_name, toDirection(s_direction));
		return t;
	}
	return NULL;
}

}
