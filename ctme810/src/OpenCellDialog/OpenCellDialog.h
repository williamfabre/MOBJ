#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CellWidget/CellWidget.h"

namespace Netlist {

// Exercice de style: dans SaveCellDialog, le widget est créé dans le CellViewer
// puis lancé (affiché) selon les besoins avec la méthode SaveCellDialog::run().
// Dans OpenCellDialog, transformer la méthode OpenCellDialog::run() en méthode
// statique qui créera à la volée un OpenCellDialog (et le détruira sitôt le résultat obtenu).

class OpenCellDialog : public QDialog {
	Q_OBJECT;
protected:
	QLineEdit * lineEdit_ ;

public:
	OpenCellDialog (QWidget* parent = NULL);
	static bool run(QWidget* parent, QString& name);
	const QString getCellName() const;
	void setCellName(const QString &);
};
}
