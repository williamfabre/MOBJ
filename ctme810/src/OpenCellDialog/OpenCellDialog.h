#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CellWidget/CellWidget.h"

namespace Netlist {

class OpenCellDialog : public QDialog {
	Q_OBJECT;
protected:
	QLineEdit * lineEdit_ ;

public:
	OpenCellDialog (QWidget * parent = NULL);
	bool run(QString& name);
	const QString getCellName() const;
	void setCellName(const QString &);
};
}
