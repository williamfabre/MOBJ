#include "Indentation.h"

namespace Netlist {


Indentation  indent;


Indentation::Indentation (): _tabulationSize(2), _indentation()
{

}

/* renvoie direct */
Indentation& Indentation::operator++ ()
{
	_indentation.append ( _tabulationSize, ' ' );
	return *this;
}

/* sauvegarde et renvoie */
Indentation  Indentation::operator++ (int)
{
	Indentation before (*this);

	_indentation.append ( _tabulationSize, ' ' );
	return before;
}


Indentation& Indentation::operator-- ()
{
	if ( _indentation.length() > _tabulationSize )
		_indentation.resize ( _indentation.length() - _tabulationSize );
	else
		_indentation.clear ();
	return *this;
}


Indentation  Indentation::operator-- (int)
{
	Indentation before (*this);

	if ( _indentation.length() > _tabulationSize )
		_indentation.resize ( _indentation.length() - _tabulationSize );
	else
		_indentation.clear ();
	return before;
}


ostream& operator<< ( ostream& o, const Indentation& indent )
{
	o << indent._indentation;
	return o;
}

}  // Netlist namespace.
