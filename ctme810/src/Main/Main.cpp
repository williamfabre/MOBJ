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

#include "CellViewer/CellViewer.h"
#include <QApplication>
#include <QtGui>
#include "Error/Error.h"

int main (int argc , char* argv [])
{
	int rvalue = -1;

	cout << "Chargement des modeles..." << endl;

	Cell::load("vdd");
	Cell::load("gnd");
	Cell::load("TransistorN");
	Cell::load("TransistorP");
	Cell::load("xor2");
	Cell::load("or2");
	Cell::load("and2");
	try {
		Cell* halfadder = Cell::load("halfadder");
		QApplication* qa = new QApplication(argc ,argv);
		CellViewer* viewer = new CellViewer();
		viewer->setCell(halfadder);
		viewer->show ();
		rvalue = qa->exec();
		delete qa;
	}
	catch (int& e) {
		cerr  << __func__ << "[ERROR] code: " << e << endl;
		exit (1);
	}
	catch (Error& e) {
		cerr  << __func__ << "[ERROR] " << e.what() << endl;
		exit (1);
	}
	catch (...) {
		cerr  << __func__ << "[ERROR] Dans quel etat j’erre." << endl;
		exit (1);
	}

	return rvalue;
}

//while(true) {

//switch(state) {
//  Reading  node  contents.
//}
// End  switch(state).
//throw  Error("[ERROR]␣Cell:: fromXml ():␣Unknown␣or␣misplaced␣tag.");
//}
// End  while(true).
