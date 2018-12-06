#ifndef  NETLIST_CELLS_LIB_H
#define  NETLIST_CELLS_LIB_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "CellsModel/CellsModel.h"
#include <QCloseEvent>

namespace Netlist {

class CellViewer;

class CellsLib : public QWidget{
	Q_OBJECT;
public:
	CellsLib(QWidget* parent=NULL);
	void setCellViewer(CellViewer*);
	int getSelectedRow() const;
	inline CellsModel* getBaseModel();
	inline void setCell(Cell*);
	public slots:
		void load ();

private:
	CellViewer* cellViewer_;
	CellsModel* baseModel_;
	QTableView* view_;
	QPushButton* load_;
};

inline CellsModel* CellsLib::getBaseModel() {return baseModel_;}
inline void CellsLib::setCell(Cell* cell){baseModel_->setCell(cell);}
};

#endif //  NETLIST_CELLS_LIB_H_
