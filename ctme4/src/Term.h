#ifndef  NETLIST_TERM_H_
#define  NETLIST_TERM_H_

#include <string>
#include "Node.h"

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
	static std::string toString(Type);
	static std::string toString(Direction);
	static Direction toDirection(std::string);

private:
	void* owner_;
	std::string name_;
	Direction direction_;
	Type type_;
	Net* net_;
	Node node_;

public:
	// Concrètement, le nouveau connecteur (Term) devra être ajouté à la liste,
	// soit de la Cell, soit de l'Instance pour laquelle il vient d'être créé.
	//
	// Dans le cas d'un terminal d'Instance, il s'agit de dupliquer intégralement
	// le Term du modèle dans l'instance. Il est proche (mais pas identique) 
	// à un constructeur par copi

	// CTOR Terminal appartenant a une Cell.
	Term (Cell* ce, const std::string& name, Direction d);
	// CTOR Terminal appartenant a une Instance.
	Term (Instance* in, const Term* modelTerm);

	// DTOR
	// Inversement, le destructeur devra le retirer de son propriétaire.
		~Term ();

	// getters
	inline bool isInternal() const;
	inline bool isExternal() const;
	inline const std::string& getName() const;
	// getNode(): elle renvoie un pointeur sur l'attribut node_. Cela
	// permettra d'accéder au modificateur Node::setId() (au TME6).
	inline Node* getNode();
	inline Net* getNet() const;
	inline Cell* getCell() const;
	Cell* getOwnerCell() const; // TODO
	inline Instance* getInstance() const;
	inline Direction getDirection() const;
	inline Peint getPosition() const; // TODO
	inline Type getType() const;

	// setters
	
	// La connexion d'un Term à un Net déterminé, c'est à dire la création 
	// des arcs du graphe, est répartie entre les méthodes Term::setNet(Net*)
	// et Net::add(Node*).
	void setNet(Net*);
	void setNet(const std::string&);
	inline void setDirection(Direction d);
	void setPosition(const Point&);
	void setPosition(int x, int y);
};

// Implementation of inline functions
inline bool Term::isInternal() const {return type_ == Internal;}

inline bool Term::isExternal() const {return type_ == External;}

inline const std::string& Term::getName() const {return name_;}

inline Node* Term::getNode() {return &node_;}

inline Net* Term::getNet() const {return net_;}

inline Cell* Term::getCell() const{
	return (type_ == External) ? static_cast<Cell*>(owner_)
		: NULL;
}

inline Instance* Term::getInstance() const{
	return (type_ == Internal) ? static_cast<Instance*>(owner_)
		: NULL;
}

inline Term::Direction Term::getDirection() const {return direction_;}

inline Term::Type Term::getType() const {return type_;}

inline void Term::setDirection(Direction d) {direction_ = d;}


}  // Netlist namespace.

#endif //  NETLIST_INDENTATION_H
