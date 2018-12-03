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

int main (int argc , char* argv [])
{
	Cell::load( "vdd" );
	Cell::load( "gnd" );
	Cell::load( "TransistorN" );
	Cell::load( "TransistorP" );
	Cell::load( "xor2" );
	Cell::load( "or2" );
	Cell::load( "and2" );
	Cell* halfadder = Cell::load("halfadder");

	QApplication* qa = new QApplication(argc ,argv);
	CellViewer* viewer = new CellViewer();
	viewer->setCell(halfadder);
	viewer->show ();
	int rvalue = qa->exec();

	delete qa;

	return rvalue;
}
