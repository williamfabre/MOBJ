#include <iostream>
#include "Indentation.h"
#include "Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"

namespace Netlist {

using namespace std;

Term::Term(Cell* ce, const std::string& name, Term::Direction d) :
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
	// TODO
}

std::string Term::toString(Term::Type type)
{
	if (type == Term::Internal)
		return "Internal";
	return "External";
}

std::string Term::toString(Term::Direction direction)
{
	std::string dir;

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

Term::Direction Term::toDirection(std::string stri)
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


void Term::setNet(const std::string& str)
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

void Term::toXml(std::ostream& o)
{
	//std::string dir;
	o << indent << "<term name=\"" << name_ << "\"";
	o << " direction=\"" << Term::toString(direction_) << "\"/>";
	o << std::endl;
}



}
