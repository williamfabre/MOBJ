#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H

#include <string>
#include <vector>
#include <libxml/xmlreader.h>
using namespace std;

#include "Term/Term.h"

namespace Netlist
{

class Cell;
class Node;

class Net {
private:

	Cell* owner_;
	std::string name_;
	// Ces numéros sont gérés au niveau de la Cell. grace a
	// newNetId();
	unsigned int id_;
	Term::Type type_;
	vector<Node*> nodes_;
	vector<Line*> lines_;

public:
	//  A la création d'un Net le tableau de Node*, nodes_ est vide, c'est à
	//  dire qu'aucun Term n'y est relié.
	//
	// Constructeurs & Destructeur. Ils devront gérer l'ajout
	// et le retrait du Net au niveau de la Cell:
	Net(Cell* cell, const std::string& str, Term::Type t);


	// Un Net connecte des Term ensemble, mais il ne les possède pas.
	// Dans le destructeur, il va donc les détacher (déconnecter)
	// mais pas les détruire.
	~Net();

	// getters
	Cell* getCell() const;
	const std::string& getName() const;
	unsigned int getId() const;
	Term::Type getType() const;
	const std::vector<Node*>& getNodes() const;
	// TME7
	Node* getNode(int index);

	// La méthode getFreeNodeId() renverra l'index de la première
	// case libre dans le tableau nodes_
	//
	// Si aucune case n'est libre, elle renverra la taille du tableau,
	// c'est à dire l'index situé immédiatement après le dernier élément.
	// Ce choix facilite l'écriture de la méthode Net::add(Node*).
	size_t getFreeNodeId() const;

	//setters

	// La connexion d'un Term à un Net déterminé, c'est à dire la création
	// des arcs du graphe, est répartie entre les méthodes Term::setNet(Net*)
	// et Net::add(Node*). On choisit de mettre le principal travail de mise à
	// jour des pointeurs et des index dans Net::add(Node*)
	// C'est cette méthode qui gérera le tableau nodes_ ainsi que les index des Node.
	// Avant son rangement dans le tableau, un Node peut soit avoir un index
	// déjà défini, ce qui indique la case qu'il souhaite occuper, soit valoir
	// Net::noid, qui veut dire qu'on le mettra dans la première case libre du
	// tableau (on l'ajoute en fin de tableau s'il est complet).
	void add(Node* node);

	bool remove(Node* node);

	// TME7 begin
        inline const std::vector<Line*>& getLines () const
        {
		return lines_;
	}
	void  add(Line* line);
        bool  remove(Line* line);
	// TME7 end


	// to xml
	void toXml(std::ostream& o);
	static Net* fromXml(Cell* cell, xmlTextReaderPtr reader);
};

/* En plus des Node, un Net doit connaître et gérer des Line.

    Il possède donc un nouvel attribut: vector<Line*> lines_.

    Et les méthodes associées:

        Méthode getLines():

        inline const std::vector<Line*>& Net::getLines () const
        { return lines_; }

        Méthode add():

        void  Net::add ( Line* line )
        { if (line) lines_.push_back( line ); }

        Méthodes remove():

        bool  Net::remove ( Line* line )
        {
          if (line) {
            for ( vector<Line*>::iterator il = lines_.begin()
                ; il != lines_.end() ; ++il ) {
              if (*il == line) {
                lines_.erase( il );
                return true;
              }
            }
          }
          return false;
        }

    Il vous reste à modifier les méthodes Net::toXml() et Net::fromXml(). */
}
# endif //  NETLIST_INDENTATION_H
