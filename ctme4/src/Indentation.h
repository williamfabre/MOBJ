#ifndef  NETLIST_INDENTATION_H
#define  NETLIST_INDENTATION_H

#include <string>
#include <iostream>
using namespace std;

namespace Netlist {


class Indentation {
public:
	Indentation ();
	Indentation& operator++(); // prefix operator
	Indentation  operator++(int); // postfix operator
	Indentation& operator--();
	Indentation  operator--(int);
private:
	size_t _tabulationSize;
	string _indentation;

	friend ostream& operator<< ( ostream&, const Indentation& );
};

extern Indentation indent;

}  // Netlist namespace.

#endif //  NETLIST_INDENTATION_H
