#ifndef  NETLIST_CELL_VIEWER_H
#define  NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include "CellWidget/CellWidget.h"
#include "SaveCellDialog/SaveCellDialog.h"
#include "OpenCellDialog/OpenCellDialog.h"
#include "InstancesWidget/InstancesWidget.h"
#include "CellsLib/CellsLib.h"

namespace Netlist {
class Cell;

class CellViewer : public QMainWindow {
	Q_OBJECT;
private:
	CellWidget* cellWidget_;
	SaveCellDialog* saveCellDialog_;
	//OpenCellDialog* openCellDialog_;
	CellsLib* cellsLib_;// TME9+.
	InstancesWidget* instancesWidget_;// TME9+.

public:
	CellViewer(QWidget* parent=NULL);
	virtual ~CellViewer();
	void setCell(Cell* cell) {
		cellWidget_->setCell(cell);
		instancesWidget_->setCell(cell);
		cellsLib_->setCell(cell);
	}
	Cell* getCell()  const { return cellWidget_->getCell(); }

	inline  CellsLib* getCellsLib() { return cellsLib_; }// TME9+.

	// NE PAS OUBLIER LE PUBLIC SLOT SINON CA MARCHE PAS BAH OUI
	public slots:
		void saveCell();
		void openCell();
		void showCellsLib();// TME9+.
		void showInstancesWidget();// TME9+.
	signals:
		// pour la mise a jour
		void cellLoaded();
};

}

#endif
