#include "CellViewer/CellViewer.h"
#include "CellWidget/CellWidget.h"
#include "Cell/Cell.h"
#include "InstancesWidget/InstancesWidget.h"
#include "CellsLib/CellsLib.h"


#include <QAction>
#include <QMenuBar>
#include <QMenu>

namespace Netlist {

CellViewer::CellViewer(QWidget * parent) :
	QMainWindow(parent), cellWidget_(NULL), cellsLib_(NULL),
	instancesWidget_(NULL), saveCellDialog_(NULL)
{
	// instanciation
	cellWidget_ = new CellWidget();
	saveCellDialog_ = new SaveCellDialog(this);
	instancesWidget_ = new InstancesWidget();
	cellsLib_ = new CellsLib();

	// set this into instance and cells
	instancesWidget_->setCellViewer(this);
	cellsLib_->setCellViewer(this);

	//set the widget
	setCentralWidget (cellWidget_);

	// File
	QMenu* fileMenu = menuBar()->addMenu("&File");

	// Save
	QAction* action = new QAction("&Save As", this);
	action->setStatusTip("Save to disk (rename)the Cell");
	action->setShortcut(QKeySequence ("CTRL+S"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(saveCell()));

	// Open
	action = new QAction("&Open", this);
	action->setStatusTip("Open a cell");
	action->setShortcut(QKeySequence ("CTRL+O"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(openCell()));

	// Cellslib
	action = new QAction("&CellsLib", this);
	action->setStatusTip("Open Cells Lib");
	action->setShortcut(QKeySequence ("CTRL+C"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(showCellsLib()));

	// InstanceWidget
	action = new QAction("&InstancesWidget", this);
	action->setStatusTip("Open Instances Widget");
	action->setShortcut(QKeySequence ("CTRL+I"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(showInstancesWidget()));

	// Quit
	action = new QAction("&Quit", this);
	action->setStatusTip("Exit the Netlist Viewer");
	action->setShortcut(QKeySequence ("CTRL+Q"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(close()));

	// connect obj1, signal, obj2, slot
	// on connecte le signal qui dit qu'on a load une cell a la fonction de
	// mise a jour o/
	// on doit recuperer l'objet du model de base
	connect(this, SIGNAL(cellLoaded()), cellsLib_->getBaseModel(), SLOT(updateDatas()));
}

CellViewer::~CellViewer(){}

void CellViewer::saveCell()
{
	Cell* cell = getCell();

	if (cell == NULL)return ;

	QString cellName = cell->getName().c_str();

	if (saveCellDialog_->run(cellName)){
		cell->setName(cellName.toStdString());
		cell->save(cellName.toStdString());
	}
}


void CellViewer::openCell()
{
	QString name;

	if (OpenCellDialog::run(this, name)){

		Cell* cell = Cell::find(name.toStdString());
		if (!cell){
			cell = Cell::load(name.toStdString());
			instancesWidget_->setCell(cell);
			emit cellLoaded();
		} else {
			setCell(cell);
		}
	}
}

void CellViewer::showInstancesWidget()
{
	cerr << __func__ << endl;
	instancesWidget_->show();
}

void CellViewer::showCellsLib()
{
	cerr << __func__ << endl;
	cellsLib_->show();
}

}
