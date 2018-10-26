#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
	cout << "Chargement des modeles:" << endl;
	cout << "- <and2> ..." << endl;
	Cell* and2 = Cell::load("and2");
	cout << "\nContenu du <and2>:" << endl;
	and2->toXml(cout);

	cout << "- <or2> ..." << endl;
	Cell* or2 = Cell::load("or2");
	cout << "\nContenu du <or2>:" << endl;
	or2->toXml(cout);

	cout << "- <xor2> ..." << endl;
	Cell* xor2 = Cell::load("xor2");
	cout << "\nContenu du <xor2>:" << endl;
	xor2->toXml(cout);

	cout << "- <halfadder> ..." << endl;
	Cell* halfadder = Cell::load("halfadder");

	cout << "\nContenu du <halfadder>:" << endl;
	halfadder->toXml(cout);

	return 0;
}

