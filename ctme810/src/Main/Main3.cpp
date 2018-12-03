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
	//cout << "Chargement des modeles:" << endl;
	//cout << "- <and2> ..." << endl;
	Cell* and2 = Cell::load("and2");
	and2->save();
	//cout << "\nContenu du <and2>:" << endl;
	//and2->toXml(cout);

	//cout << "- <or2> ..." << endl;
	Cell* or2 = Cell::load("or2");
	or2->save();
	//cout << "\nContenu du <or2>:" << endl;
	//or2->toXml(cout);

	//cout << "- <xor2> ..." << endl;
	Cell* xor2 = Cell::load("xor2");
	xor2->save();
	//cout << "\nContenu du <xor2>:" << endl;
	//xor2->toXml(cout);


	//cout << "- <halfadder> ..." << endl;
	Cell* halfadder = Cell::load("halfadder");

	//cout << "\nContenu du <halfadder>:" << endl;
	//halfadder->toXml(cout);
	halfadder->save();

	delete halfadder;
	delete xor2;
	delete or2;
	delete and2;

	return 0;
}

