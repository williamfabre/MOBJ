#include <vector>
#include <libxml/xmlreader.h>

#include "Instance.h"
#include "Cell.h"
#include "Term.h"
#include "XmlUtil.h"

namespace Netlist {

Instance::Instance(Cell* owner, Cell* model, const string& str) :
	owner_(owner),
	masterCell_(model),
	name_(str),
	terms_(),
	position_()
{
	for (vector<Term*>::const_iterator it = model->getTerms().begin();
		it != model->getTerms().end(); it++){
		terms_.push_back(new Term(this, *it));
	}

	owner_->add(this);
}


Instance::~Instance()
{
	//Duplication
	// FATAL ERROR 5H DE DEBUG
	for (vector<Term*>::const_iterator it = terms_.begin();
		it != terms_.end(); it++){
		delete *it;
	}

	owner_->remove(this);
}


// getters
const string& Instance::getName() const
{
	return name_;
}


Cell* Instance::getMasterCell() const
{
	return masterCell_;
}


Cell* Instance::getCell() const
{
	return owner_;
}


const vector<Term*>& Instance::getTerms() const
{
	return terms_;
}


Term* Instance::getTerm(const string& name) const
{
	for ( vector<Term*>::const_iterator iterm=terms_.begin();
	      iterm != terms_.end() ; ++iterm ) {
		if ((*iterm)->getName() == name)  return *iterm;
	}
	return NULL;
}


Point Instance::getPosition() const
{
	return position_;
}


//setters
bool Instance::connect(const string& name, Net* net)
{
	// TODO check if it works
	Term* t = NULL;

	for (vector<Term*>::const_iterator it = terms_.begin();
		it != terms_.end(); it++){

		if ((*it)->getName() == name)
			t = *it;
	}

	if (t == NULL) return false;

	t->setNet(net);
	return true;
}


void Instance::add(Term* term)
{
	if (getTerm(term->getName())) {
		cerr << "[ERROR] Attemp to add duplicated terminal <";
		cerr << term->getName() << ">." << endl;
		exit(1);
	}
	terms_.push_back(term);
}


// TODO
/* EEEEEEEEEEENORME PROBLEME JE SUIS OBLIGE D'AJOUTER 2 FOIS POUR QUE
 * CETTE SUPRESSION FONCTIONNE
 */
void Instance::remove(Term* term)
{
	// en C++98 elle prend un iterator et pas un const
	for (vector<Term*>::iterator iterm=terms_.begin();
	     *iterm != NULL && iterm != terms_.end() ; ++iterm) {
		if (*iterm == term){
			cerr << "supp : " << term->getName() << "==";
			cerr << (*iterm)->getName() << endl;
			terms_.erase(iterm);
			return;
		}
	}
}


void Instance::setPosition(const Point& pt)
{
	position_ = pt;
}


void Instance::setPosition(int x, int y)
{
	position_ = Point (x, y);
}


void Instance::toXml(ostream& o)
{
	o << indent << "<instance name=\"" << name_ << "\"";
	o << " mastercell=\"" << masterCell_->getName() << "\"";
	o << " x=\"" << position_.getX() << "\"";
	o << " y=\"" << position_.getY() << "\"";
	o << "/>" << endl;
}

Instance* Instance::fromXml(Cell* cell, xmlTextReaderPtr reader)
{
	string s_name;
	string s_mastercell;
	string s_x;
	string s_y;

	xmlChar* xml_name_value;
	xmlChar* xml_mastercell_value;
	xmlChar* xml_x_value;
	xmlChar* xml_y_value;

	const xmlChar* xml_name;
	const xmlChar* xml_mastercell;
	const xmlChar* xml_x;
	const xmlChar* xml_y;

	// s'il y a declaration d'un name
	xml_name = (const xmlChar*)"name";
	xml_mastercell = (const xmlChar*)"mastercell";
	xml_x = (const xmlChar*)"x";
	xml_y = (const xmlChar*)"y";

	// prendre la valeur de la declaration
	xml_name_value = xmlTextReaderGetAttribute(reader, xml_name);
	xml_mastercell_value = xmlTextReaderGetAttribute(reader,xml_mastercell);
	xml_x_value = xmlTextReaderGetAttribute(reader, xml_x);
	xml_y_value = xmlTextReaderGetAttribute(reader, xml_y);

	// transformer cette valeur en string
	s_name = xmlCharToString(xml_name_value);
	s_mastercell = xmlCharToString(xml_mastercell_value);
	s_x = xmlCharToString(xml_x_value);
	s_y = xmlCharToString(xml_y_value);

	// Si le nom n'est pas vide alors on demande
	// la creation de la cellule
	if (not (s_name.empty() && s_mastercell.empty() && s_x.empty()
		 && s_y.empty())) {

		Cell* mastercell;
		if (!(mastercell= Cell::find(s_mastercell)))
			return NULL;

		int x = atoi(s_x.c_str());
		int y = atoi(s_y.c_str());

		Instance *instance;
		instance = new Instance(cell, mastercell, s_name);
		instance->setPosition(x, y);

		return instance;
	}
	return NULL;
}

}
