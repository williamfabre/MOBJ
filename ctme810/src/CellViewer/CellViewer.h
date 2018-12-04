#ifndef  NETLIST_CELL_VIEWER_H
#define  NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include "CellWidget/CellWidget.h"
#include "SaveCellDialog/SaveCellDialog.h"
#include "OpenCellDialog/OpenCellDialog.h"

namespace Netlist {
class Cell;
class InstancesWidget;
class CellsLib;


class CellViewer : public QMainWindow {
	Q_OBJECT;
public:
	CellViewer(QWidget* parent=NULL);
	virtual ~CellViewer();
	void setCell(Cell* cell) { cellWidget_->setCell(cell); }
	Cell* getCell()  const { return cellWidget_->getCell(); }
	inline  CellsLib* getCellsLib();  // TME9+.

	// NE PAS OUBLIER LE PUBLIC SLOT SINON CA MARCHE PAS BAH OUI
	public slots:
		void saveCell();
		void openCell();
		void showCellsLib();  // TME9+.
		void showInstancesWidget();  // TME9+.
private:
	CellWidget* cellWidget_;
	SaveCellDialog* saveCellDialog_;
	//OpenCellDialog* openCellDialog_;
	CellsLib* cellsLib_;         // TME9+.
	InstancesWidget* instancesWidget_;  // TME9+.

};

}

#endif
