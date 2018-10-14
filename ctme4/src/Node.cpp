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

Node::Node(Term* term, size_t id) : id_(id), term_(term), position_()
{
	return;
}


Node::~Node ()
{
	if (getNet())
		getNet()->remove(this);
}


inline Net* Node::getNet() const {return term_->getNet();}


// Node::toXml() à écrire ici.


}  // Netlist namespace.
