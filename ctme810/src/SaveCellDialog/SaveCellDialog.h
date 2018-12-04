#ifndef  NETLIST_SAVE_CELL_DIALOG_H
#define  NETLIST_SAVE_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Netlist {

class CellWidget;


// Exercice de style: dans SaveCellDialog, le widget est créé dans le CellViewer
// puis lancé (affiché) selon les besoins avec la méthode SaveCellDialog::run().
// Dans OpenCellDialog, transformer la méthode OpenCellDialog::run() en méthode
// statique qui créera à la volée un OpenCellDialog (et le détruira sitôt le résultat obtenu).
class SaveCellDialog : public QDialog {
	Q_OBJECT;
protected:
	QLineEdit* lineEdit_;

public:
	SaveCellDialog (QWidget* parent=NULL);


// Le SaveCellDialog, contrairement à ce que son nom laisse penser, n'effectue pas lui-même
// la sauvegarde de la cellule. Il se contente de demander à l'utilisateur
// quel nom il souhaite donner à la cellule à sauvegarder. Ce qui est récupéré
// par l'appel à la méthode (statique) SaveCellDialog::run(QString& name)
// est juste le nom sous lequel on va effectuer la sauvegarde.
// D'où le passage par référence de l'argument name.
// La sauvegarde sera réellement faite dans la méthode CellViewer::saveCell().
	bool run(QString& name);
	const QString getCellName()  const;
	void setCellName(const  QString&);
};
}

#endif
