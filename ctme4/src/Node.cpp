#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"

namespace Netlist {

using namespace std;

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
void Node::toXml(std::ostream& o)
{
	o << indent << "<node term=\"" << term_->getName() << "\"";
	if (term_->isInternal())
		o << " instance=\"" << term_->getInstance()->getName() << "\"";

	o << " id=\"" << id_ << "\"";
	o << " x=\"" << position_.getX() << "\"";
	o << " y=\"" << position_.getY() << "\"/>";
	o << endl;
}



}  // Netlist namespace.
