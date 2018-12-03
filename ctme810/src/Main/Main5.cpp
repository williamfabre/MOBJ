// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/7>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term/Term.h"
#include "Net/Net.h"
#include "Instance/Instance.h"
#include "Cell/Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
	//cout << "Chargement des modeles..." << endl;
	Cell::load( "vdd" );
	Cell::load( "gnd" );
	Cell::load( "TransistorN" );
	Cell::load( "TransistorP" );
	Cell::load( "xor2" );
	//Cell::load( "or2" );
	Cell::load( "and2" );
	Cell::load( "inverter" );
	//Cell* halfadder = Cell::load( "halfadder" );
	//Cell* fa = Cell::load( "fulladder" );
	Cell* or2= Cell::load( "or2" );

	//cout << "\nContenu du <halfadder>:" << endl;
	//halfadder->toXml( cout );
	//cout << "\nContenu du <fulladder>:" << endl;
	//fa->toXml( cout );
	cout << "\nContenu du <or2>:" << endl;
	or2->toXml( cout );



	return 0;
}
