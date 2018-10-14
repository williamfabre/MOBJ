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
	Term (Cell* ce, const std::string& name, Direction d);
	Term (Instance* in, const Term* modelTerm);
	~Term ();

	// getters
	inline bool isInternal() const;
	inline bool isExternal() const;
	inline const std::string& getName() const;
	inline Node* getNode();
	inline Net* getNet() const;
	inline Cell* getCell() const; // TODO
	Cell* getOwnerCell() const;
	inline Instance* getInstance() const;
	inline Direction getDirection() const;
	inline Point getPosition() const; // TODO
	inline Type getType() const;

	// setters
	void setNet(Net*);
	void setNet(const std::string&);
	inline void setDirection(Direction d);
	void setPosition(const Point&);
	void setPosition(int x, int y);
};

	inline bool Term::isInternal() const {return type_ == Internal;}
	inline bool Term::isExternal() const {return type_ == External;}
	inline const std::string& Term::getName() const {return name_;}
	inline Node* Term::getNode() {return &node_;}
	inline Net* Term::getNet() const {return net_;}
	inline Term::Direction Term::getDirection() const {return direction_;}
	inline Term::Type Term::getType() const {return type_;}

	inline void Term::setDirection(Direction d) {direction_ = d;}


}  // Netlist namespace.

#endif //  NETLIST_INDENTATION_H
