#include <vector>
#include <libxml/xmlreader.h>

#include "Instance.h"
#include "Cell.h"
#include "Term.h"

namespace Netlist {

Instance::Instance(Cell* owner, Cell* model, const string& str) :
	owner_(owner),
	masterCell_(model),
	name_(str),
	terms_(),
	position_()
{
	vector<Term*>::const_iterator it = model->getTerms().begin();
	vector<Term*>::const_iterator end = model->getTerms().end();

	//Duplication
	for (; it != end; it++)
		new Term(this, *it);

	owner_->add(this);
}


Instance::~Instance()
{
	vector<Term*>::const_iterator it = terms_.begin();
	vector<Term*>::const_iterator end = terms_.end();

	//Duplication
	for (; it != end; it++)
		delete *it;

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
	vector<Term*>::const_iterator it = terms_.begin();
	vector<Term*>::const_iterator end = terms_.end();

	for (; it != end; it++){
		if ((*it)->getName() ==  name)
			return *it;
	}
	return NULL;
}


Point Instance::getPosition() const
{
	return position_;
}


//setters
bool Instance::connect( const string& name, Net* net)
{
	// TODO check if it works
	Term* t = NULL;
	vector<Term*>::const_iterator it = terms_.begin();
	vector<Term*>::const_iterator end = terms_.end();

	for (; it != end; it++) {
		if ((*it)->getName() == name)
			t = *it;
	}

	if (t == NULL) return false;

	t->setNet(net);
	return true;
}


void Instance::add(Term* t)
{
	terms_.push_back(t);
}


void Instance::remove(Term* t)
{
	vector<Term*>::iterator it = terms_.begin();
	vector<Term*>::iterator end = terms_.end();

	for ( ; it != end; it++) {
		if ((*it) == t)
			// en C++98 elle prend un iterator et pas
			// un const
			terms_.erase(it);
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
	return NULL;
}

}
