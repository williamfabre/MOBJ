#ifndef NETLIST_NODE_H
#define NETLIST_NODE_H

#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Point.h"

namespace Netlist {

class Term;
class Net;

class Node {
protected:
	size_t id_;
	Term* term_;
	Point position_;
public:
	// id du node
	static const size_t noid;
public:
	//  A la création d'un Term, l'id_ de l'objet niché node_ est initialisé à
	//  Net::noid signifiant qu'il n'est relié à aucun Net.

	Node(Term*, size_t id=noid);
	~Node();
	inline Point getPosition() const;
	inline void setPosition(const Point&);
	inline void setPosition(int x, int y);
	inline size_t getId() const;
	Net* getNet() const;
	inline Term* getTerm() const;
	inline void setId( size_t );

	// toXml
	void toXml(std::ostream& o);
private:
	Node(const Node&);
	Node& operator=   ( const Node& );
};

inline size_t Node::getId() const {return id_;}
inline Term* Node::getTerm() const {return term_;}
inline Point Node::getPosition() const {return position_;}

inline void Node::setId(size_t id ) {id_=id;}
inline void Node::setPosition(const Point& pos) {position_ = pos;}
inline void Node::setPosition(int x, int y ) {position_ = Point(x,y);}

}  // Netlist namespace.

#endif  // NETLIST_NODE_H
