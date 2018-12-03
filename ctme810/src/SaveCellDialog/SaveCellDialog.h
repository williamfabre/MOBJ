#ifndef  NETLIST_SAVE_CELL_DIALOG_H
#define  NETLIST_SAVE_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Netlist {

class CellWidget;

class SaveCellDialog : public QDialog {
	Q_OBJECT;
protected:
	QLineEdit* lineEdit_;

public:
	SaveCellDialog (QWidget* parent=NULL);
	bool run(QString& name);
	const QString getCellName()  const;
	void setCellName(const  QString&);
};
}

#endif
