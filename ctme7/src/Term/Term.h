#ifndef  NETLIST_TERM_H_
#define  NETLIST_TERM_H_

#include <libxml/xmlreader.h>
#include <string>
using namespace std;

#include "Node/Node.h"

namespace Netlist {

class Cell;
class Point;
class Instance;
class Net;

class Term {

public:
	enum Type {Internal=1, External=2};
	enum Direction {In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6};

	// Trois methodes statiques ajoutees a la classe Term pour convertir
	// depuis/vers une chaine de caractere (string).
	static string toString(Type);
	static string toString(Direction);
	static Direction toDirection(string);
	static Type toType(string);

private:
	void* owner_;
	string name_;
	Direction direction_;
	Type type_;
	Net* net_;
	NodeTerm node_;

public:
	// Concrètement, le nouveau connecteur (Term) devra être ajouté à la liste,
	// soit de la Cell, soit de l'Instance pour laquelle il vient d'être créé.
	//
	// Dans le cas d'un terminal d'Instance, il s'agit de
	// dupliquer intégralement. le Term du modèle dans l'instance.
	// Il est proche (mais pas identique) à un constructeur par copi.
	// CTOR
	Term (Cell* ce, const string& name, Direction d);
	Term (Instance* in, const Term* modelTerm);

	// DTOR
	// Inversement, le destructeur devra le retirer de son propriétaire.
	// Lorsqu'un Term est détruit, si il est accroché à un Net,
	// il doit s'en déconnecter dans son destructeur.

	~Term ();

	// getters
	inline bool isInternal() const;
	inline bool isExternal() const;
	inline const string& getName() const;
	// getNode(): elle renvoie un pointeur sur l'attribut node_. Cela
	// permettra d'accéder au modificateur Node::setId() (au TME6).
	inline NodeTerm* getNode();
	inline Net* getNet() const;
	inline Cell* getCell() const;
	// ::getOwnerCell() renvoie la Cell dans laquelle l'objet se trouve,
	// ce qui, dans le cas d'un Term d'instance est la Cell possédant celle-ci.
	Cell* getOwnerCell() const;
	// Dit encore autrement, les méthodes ::getCell() et ::getInstance()
	// renvoient l'objet auquel le Term appartient. Donc, dans le cas d'un
	// Term appartenant à une instance ::getCell() renverra NULL. En revanche,
	inline Instance* getInstance() const;
	inline Direction getDirection() const;
	inline Point getPosition() const; 
	inline Type getType() const;

	// setters

	// La connexion d'un Term à un Net déterminé, c'est à dire la création
	// des arcs du graphe, est répartie entre les méthodes Term::setNet(Net*)
	// et Net::add(Node*).
	//
	// Méthode setNet(): C'est dans cette méthode que le chaînage entre Net,
	// Term et Node sera réalisé (en appelant les méthodes appropriées du Net).
	//
	// Si un pointeur NULL est passé en argument, cela signifie que le Term
	// doit être déconnecté (s'il était relié à un Net).
	//
	// Le Net peut être spécifié directement par un pointeur ou bien par
	// son nom, c'est la deuxième surcharge de setNet().
	void setNet(Net*);
	void setNet(const string&);
	inline void setDirection(Direction d);
	void setPosition(const Point&);
	void setPosition(int x, int y);


	// ostream methode
	void toXml(ostream& o);

	static Term* fromXml(Cell* cell, xmlTextReaderPtr reader);
};

// Implementation of inline functions
// Getters
inline bool Term::isInternal() const {return type_ == Internal;}

inline bool Term::isExternal() const {return type_ == External;}

inline const string& Term::getName() const {return name_;}

inline NodeTerm* Term::getNode() {return &node_;}

inline Net* Term::getNet() const {return net_;}

inline Cell* Term::getCell() const
{
	return (type_ == External) ? static_cast<Cell*>(owner_)
		: NULL;
}

inline Instance* Term::getInstance() const
{
	return (type_ == Internal) ? static_cast<Instance*>(owner_)
		: NULL;
}

inline Term::Direction Term::getDirection() const {return direction_;}

inline Term::Type Term::getType() const {return type_;}

inline Point Term::getPosition() const {return node_.getPosition();}



// Setters
inline void Term::setDirection(Direction d) {direction_ = d;}


}  // Netlist namespace.

#endif //  NETLIST_INDENTATION_H
