#ifndef NETLIST_CELL_H
#define NETLIST_CELL_H

#include <iostream>
#include <string>
#include <vector>
#include "Indentation.h"

namespace Netlist {

class Instance;
class Net;
class Term;


class Cell {
private:
	static std::vector<Cell*> cells_;
	std::string             name_;
	std::vector<Term*>      terms_;
	std::vector<Instance*>  instances_;

	// Un Net est unique au niveau d'une Cell, c'est une équipotentielle.
	// Pour l'identifier, on ne se fie pas au nom, au lieu de cela on
	// utilise un identificateur (numéro) unique, stocké dans l'attribut
	// id_. Ces numéros sont gérés au niveau de la Cell.
	std::vector<Net*>       nets_;
	unsigned int            maxNetIds_;

public:

	static std::vector<Cell*>& getAllCells();

	// Recherche un modèle (Cell) dans le tableau global des modèles.
	static Cell* find( const std::string& );

public:
	// Une Cell possède ses Term, Net et Instance.
	// La Cell sera donc chargée de leur destrution. On va creer ces
	// composants dans l'ordre suivant:
	//	1) Les Term.
	//	2) Les Instance.
	//	3) Les Net.
	// CTOR (ajoute à la liste globale).
	Cell(const std::string&);

	// La Cell sera donc chargée de leur destrution. On va détruire ces
	// composants dans l'ordre suivant:
	//	1) Les Net.
	//	2) Les Instance.
	//	3) Les Term.
	// DTOR . Retire de la liste globale,
	~Cell();

	// Getters
	// Retoune le nom du modèle.
	inline const std::string& getName() const;

	// Retourne la table des instances.
	inline const std::vector<Instance*>& getInstances() const;

	// Retourne la table des connecteurs (Term).
	inline const std::vector<Term*>& getTerms() const;

	//Retourne la table des signaux (Net)
	inline const std::vector<Net*>& getNets() const;

	// Recherche une instance, NULL si non trouvée.
	Instance* getInstance(const std::string&) const;

	// Recherche un connecteur (ou renvoie NULL.
	Term* getTerm(const std::string&) const;

	// Recherche un signal (ou renvoie NULL).
	Net* getNet(const std::string&) const;

	// Setters
	void setName(const std::string&);

	// Ajoute une nouvelle Instance
	void add(Instance*);

	// Ajoute un nouveau connecteur (Term)
	void add(Term*);

	// Ajoute un nouveau signal (Net)
	void add(Net*);

	// Retire une Instance (ne le désalloue pas)
	void remove(Instance*);

	// Retire un connecteur (ne le désalloue pas)
	void remove(Term*);

	// Retire un signal (ne le désalloue pas)
	void remove(Net*);

	// Associe le connecteur name avec le signal net.
	// Renvoie true en cas de succès.
	bool connect(const std::string& name, Net* net );

	// Renvoie un nouvel identificateur de signal.
	// Il est garanti unique.
	unsigned int newNetId();

	void toXml(std::ostream& stream);
};

inline const std::string& Cell::getName() const {return name_;};

inline const std::vector<Instance*>& Cell::getInstances() const
{
	return instances_;
}

inline const std::vector<Term*>& Cell::getTerms() const {return terms_;}

inline const std::vector<Net*>& Cell::getNets() const {return nets_;}

}  // Netlist namespace.

#endif  // NETLIST_CELL_H

