#include "CellViewer/CellViewer.h"
#include "CellWidget/CellWidget.h"
#include "SaveCellDialog/SaveCellDialog.h"
#include "Cell/Cell.h"
#include <QAction>
#include <QMenuBar>
#include <QMenu>

namespace Netlist {


CellViewer::CellViewer(QWidget* parent)
	: QMainWindow(parent), cellWidget_(NULL), saveCellDialog_(NULL)
{
	cellWidget_ = new CellWidget();
	saveCellDialog_ = new SaveCellDialog(this);
	setCentralWidget(cellWidget_);

	// FILE IN MENU
	QMenu* fileMenu = menuBar()->addMenu("&File");

	// SAVE AS IN MENU
	QAction* action = new QAction("&Save As", this);
	action->setStatusTip("Save to disk (rename) the Cell");
	action->setShortcut(QKeySequence("CTRL+S"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(saveCell()));

	// QUIT IN MENU
	action = new QAction("&Quit", this);
	action->setStatusTip("Exit the Netlist Viewer");
	action->setShortcut(QKeySequence("CTRL+Q"));
	action->setVisible(true);
	fileMenu->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(close()));
}


CellViewer::~CellViewer()
{
}

void CellViewer::saveCell()
{
	// recuperer la cell
	Cell* cell = getCell();

	// si elle n'existe pas on detruit
	if (cell == NULL) return;

	// on recupere le nom de la cell
	QString cellName = cell->getName().c_str();

	// on set le nom et on sauvegarde
	if (saveCellDialog_->run(cellName)){
		cell->setName(cellName.toStdString());
		cell->save(cellName.toStdString());
		cerr << "test12341234";
	}
}

}
