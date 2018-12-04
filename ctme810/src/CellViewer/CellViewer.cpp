#include "CellViewer/CellViewer.h"
#include "CellWidget/CellWidget.h"
#include "OpenCellDialog/OpenCellDialog.h"
#include "SaveCellDialog/SaveCellDialog.h"
#include "Cell/Cell.h"
#include <QAction>
#include <QMenuBar>
#include <QMenu>

namespace Netlist {


CellViewer::CellViewer(QWidget* parent)
	: QMainWindow(parent), cellWidget_(NULL), saveCellDialog_(NULL),
	openCellDialog_(NULL)
{
	cellWidget_ = new CellWidget();
	saveCellDialog_ = new SaveCellDialog(this);
	openCellDialog_ = new OpenCellDialog(this);

	setCentralWidget(cellWidget_);

	// FILE IN MENU
	QMenu* fileMenu = menuBar()->addMenu("&File");

	// SAVE AS IN MENU
	QAction* actionSave = new QAction("&Save As", this);
	actionSave->setStatusTip("Save to disk (rename) the Cell");
	actionSave->setShortcut(QKeySequence("CTRL+S"));
	actionSave->setVisible(true);
	fileMenu->addAction(actionSave);
	connect(actionSave, SIGNAL(triggered()), this, SLOT(CellViewer::saveCell()));

	// OPEN IN MENU
	QAction* actionOpen = new QAction("&Open", this);
	actionOpen->setStatusTip("Open from disk the Cell");
	actionOpen->setShortcut(QKeySequence("CTRL+O"));
	actionOpen->setVisible(true);
	fileMenu->addAction(actionOpen);
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(CellViewer::openCell()));


	// QUIT IN MENU
	QAction* actionQuit = new QAction("&Quit", this);
	actionQuit->setStatusTip("Exit the Netlist Viewer");
	actionQuit->setShortcut(QKeySequence("CTRL+Q"));
	actionQuit->setVisible(true);
	fileMenu->addAction(actionQuit);
	connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
}


CellViewer::~CellViewer()
{
}

void CellViewer::saveCell()
{
	cerr << __func__ << "IT WORKS with Save" << endl;
	// recuperer la cell
	Cell* cell = getCell();

	// si elle n'existe pas on detruit
	if (cell == NULL) return;

	// on recupere le nom de la cell
	QString cellName = cell->getName().c_str();

	// on set le nom et on sauvegarde
	if (saveCellDialog_->run(cellName)){ // si l'execution fonctionne
		cell->setName(cellName.toStdString());
		cell->save(cellName.toStdString());
		cerr << "test12341234";
	}
}

void CellViewer::openCell()
{
	QString name;

	cerr << __func__ << "IT WORKS with Open" << endl;
	// si on est en etat run
	if (openCellDialog_->run(name)){

		Cell* cell = Cell::find(name.toStdString());
		if (!cell){
			// on load si elle n'existe pas
			cell = Cell::load(name.toStdString());
		} else {
			// on set si elle existe
			setCell(cell);
		}
	}
}

}
