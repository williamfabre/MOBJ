#include  <cstdlib>
//#include <libxml/xmlreader.h>
#include <fstream>

#include  "Cell.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "XmlUtil.h"

namespace Netlist {

vector<Cell*>  Cell::cells_;

Cell* Cell::find(const string& name)
{
	for (vector<Cell*>::iterator icell=cells_.begin();
	     icell != cells_.end() ; ++icell) {
		if ((*icell)->getName() == name) return *icell;
	}
	// TODO GROS PROBLEME, au debut de la creation on va toujours
	// creer une cell qui n'existe pas mais si on cree un cell
	// a partir de celle qui n'existe pas on a une erreur de type
	// SEGFAULT car on return NULL on ne la pas trouver et c'est tres
	// complique a retrouver.
	//cerr << "FATAL ERROR NOT FOUND" << endl;
	return NULL;
}


Cell::Cell(const string& name) : name_(name), terms_() ,instances_(), nets_()
				 ,maxNetIds_(0)
{
	if (find(name)) {
		cerr << "[ERROR] Attempt to create duplicate of Cell <";
		cerr << name << ">.\n"
			<< "        Aborting..." << endl;
		exit(1);
	}
	cells_.push_back(this);
}


Cell::~Cell()
{
	for (vector<Cell*>::iterator icell=cells_.begin() ;
	     icell != cells_.end() ; ++icell) {
		if (*icell == this) {
			cells_.erase(icell);
			break;
		}
	}

	while (not nets_.empty()) delete *nets_.begin();
	while (not instances_.empty()) delete *instances_.begin();
	while (not terms_.empty()) delete *terms_.begin();
}


Instance* Cell::getInstance (const string& name) const
{
	for (vector<Instance*>::const_iterator iinst=instances_.begin();
	     iinst != instances_.end() ; ++iinst) {
		if ((*iinst)->getName() == name)  return *iinst;
	}
	return NULL;
}


Term* Cell::getTerm (const string& name) const
{
	for ( vector<Term*>::const_iterator iterm=terms_.begin();
	      iterm != terms_.end() ; ++iterm ) {
		if ((*iterm)->getName() == name)  return *iterm;
	}
	return NULL;
}


Net* Cell::getNet (const string& name) const
{
	for (vector<Net*>::const_iterator inet=nets_.begin();
	     inet != nets_.end() ; ++inet) {
		if ((*inet)->getName() == name)  return *inet;
	}
	return NULL;
}


void Cell::setName (const string& cellName)
{
	if (cellName == name_) return;
	if (find(cellName) != NULL) {
		cerr << "[ERROR] Cell::setName() - New Cell name <";
		cerr<< cellName << "> already exists."<< endl;
		return;
	}
	name_ = cellName;
}


void Cell::add(Instance* instance)
{
	if (getInstance(instance->getName())) {
		cerr << "[ERROR] Attemp to add duplicated instance <";
		cerr << instance->getName() << ">." << endl;
		exit(1);
	}
	instances_.push_back(instance);
}


void Cell::add(Term* term)
{
	if (getTerm(term->getName())) {
		cerr << "[ERROR] Attemp to add duplicated terminal <";
		cerr << term->getName() << ">." << endl;
		exit(1);
	}
	terms_.push_back(term);
}


void Cell::add(Net* net)
{
	if (getNet(net->getName())) {
		cerr << "[ERROR] Attemp to add duplicated Net <";
		cerr << net->getName() << ">." << endl;
		exit( 1 );
	}
	nets_.push_back(net);
}


bool Cell::connect(const string& name, Net* net)
{
	Term* term = getTerm(name);
	if (term == NULL) return false;

	term->setNet(net);
	return true;
}


void  Cell::remove(Instance* instance)
{
	for (vector<Instance*>::iterator iinst=instances_.begin();
	     *iinst != NULL && iinst != instances_.end() ; ++iinst){
		if (*iinst == instance){
			instances_.erase(iinst);
			return;
		}
	}
}


void  Cell::remove(Term* term)
{
	for (vector<Term*>::iterator iterm=terms_.begin();
	     *iterm != NULL && iterm != terms_.end() ; ++iterm) {
		if (*iterm == term){
			terms_.erase(iterm);
			return;
		}
	}
}


void  Cell::remove ( Net* net )
{
	for (vector<Net*>::iterator inet=nets_.begin();
	     *inet != NULL && inet != nets_.end() ; ++inet) {
		if (*inet == net){
			nets_.erase(inet);
			return;
		}
	}
}


unsigned int Cell::newNetId ()
{ return maxNetIds_++; }


// Cell::toXml() à écrire ici...
void Cell::toXml(ostream& stream) const
{
	vector<Term*>::const_iterator itt;
	vector<Instance*>::const_iterator iti;
	vector<Net*>::const_iterator itn;


	// XML file
	stream << "<?xml version=\"1.0\"?>" << endl;

	// CELL START
	stream << indent++ << "<cell name=\"" << name_ << "\">\n";

	// TERM START
	stream << indent++ << "<terms>" << endl;
	for (itt = terms_.begin(); itt != terms_.end(); itt++)
		(*itt)->toXml(stream);
	stream << --indent << "</terms>" << endl;
	// TERM END

	// INSTANCE START
	stream << indent++ << "<instances>" << endl;
	for (iti = instances_.begin(); iti != instances_.end(); iti++)
		(*iti)->toXml(stream);
	stream << --indent << "</instances>" << endl;
	// INSTANCE END

	// NED STARK
	stream << indent++ << "<nets>" << endl;
	for(itn = nets_.begin(); itn != nets_.end(); itn++)
		(*itn)->toXml(stream);
	stream << --indent << "</nets>" << endl;
	// NED DEAD

	stream << --indent << "</cell>\n";
	// CELL END

}

Cell* Cell::fromXml(xmlTextReaderPtr reader)
{
	enum State { Init = 0
		, BeginCell
			, BeginTerms
			, EndTerms
			, BeginInstances
			, EndInstances
			, BeginNets
			, EndNets
			, EndCell
	};

	string unexpected;
	const xmlChar* cellTag;
	const xmlChar* netsTag;
	const xmlChar* termsTag;
	const xmlChar* instancesTag;

	// On declare des tags pour cell, nets, terms, instances
	cellTag = xmlTextReaderConstString(reader, (const xmlChar*)"cell");
	netsTag = xmlTextReaderConstString(reader, (const xmlChar*)"nets");
	termsTag = xmlTextReaderConstString(reader, (const xmlChar*)"terms");
	instancesTag = xmlTextReaderConstString(reader,
						(const xmlChar*)"instances");

	Cell* cell = NULL;
	State state = Init;

	unexpected = "[ERR] Cell::fromXml(): Unexpected termination of parser.";
	while (true) {
		int status = xmlTextReaderRead(reader);
		if (status != 1) {
			if (status != 0) {
				cerr << unexpected;
				cerr << endl;
			}
			break;
		}

		// On elimine les commentaires, espaces et tabs
		switch (xmlTextReaderNodeType(reader)) {
		case XML_READER_TYPE_COMMENT:
		case XML_READER_TYPE_WHITESPACE:
		case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
			continue;
		}

		// The local name of the node.
		const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);

		// On passe d'etat en etat.
		switch (state) {
		case Init:
			if (cellTag == nodeName) {
				// BEGIN CELL
				state = BeginCell;
				string cellName;
				// s'il y a declaration d'un name
				const xmlChar* xmlName = (const xmlChar*)"name";
				xmlChar* textValue;
				// prendre la valeur de la declaration
				textValue = xmlTextReaderGetAttribute(reader,
								      xmlName);
				// transformer cette valeur en string
				cellName = xmlCharToString(textValue);
				// Si le nom n'est pas vide alors on demande
				// la creation de la cellule
				if (not cellName.empty()) {
					cell = new Cell (cellName);
					// On peut passer a la def des terms
					state = BeginTerms;
					continue;
				}
			}
			break;
		case BeginTerms:
			if ((nodeName == termsTag) and (isElement(reader))){
				state = EndTerms;
				continue;
			}
			break;
		case EndTerms:
			if ((nodeName == termsTag) and (isEnd(reader))){
				state = BeginInstances;
				continue;
			} else {
				if (Term::fromXml(cell, reader)) continue;
			}

			break;
		case BeginInstances:
			if ((nodeName == instancesTag) and (isElement(reader))){
				state = EndInstances;
				continue;
			}
			break;
		case EndInstances:
			if ((nodeName == instancesTag) and (isEnd(reader))) {
				state = BeginNets;
				continue;
			} else {
				if (Instance::fromXml(cell,reader))
					continue;
			}
			break;
		case BeginNets:
			if ((nodeName == netsTag) and (isElement(reader))){
				state = EndNets;
				continue;
			}
			break;
		case EndNets:
			if ((nodeName == netsTag) and (isEnd(reader))){
				state = EndCell;
				continue;
			} else {
				if (Net::fromXml(cell,reader)) continue;
			}
			break;
		case EndCell:
			if ((nodeName == cellTag) and (isEnd(reader))){
				continue;
			}
			break;
		default:
			break;
		}

		cerr << "[ERROR] Cell::fromXml(): Unknown or misplaced tag <";
		cerr << nodeName;
		cerr << "> (line:" << xmlTextReaderGetParserLineNumber(reader);
		cerr << ")." << endl;
		break;
	}

	return cell;
}


Cell* Cell::load(const string& cellName)
{
	xmlTextReaderPtr reader;
	string cellFile = "./cells/" + cellName + ".xml";

	reader = xmlNewTextReaderFilename(cellFile.c_str());
	if (reader == NULL) {
		cerr << "[ERROR] Cell::load() unable to open file <";
		cerr << cellFile << ">." << endl;
		return NULL;
	}

	Cell* cell = Cell::fromXml(reader);
	xmlFreeTextReader(reader);

	return cell;
}


void Cell::save() const
{
	string  fileName   = "./cells/" + getName() + "_test.xml";
	fstream fileStream(fileName.c_str(),
			   ios_base::out|ios_base::trunc);

	if (not fileStream.good()) {
		cerr << "[ERROR] Cell::save() unable to open file <";
		cerr << fileName << ">." << endl;
		return;
	}

	cerr << "Saving <Cell " << getName();
	cerr << "> in <" << fileName << ">" << endl;
	toXml(fileStream);

	fileStream.close();
}


}  // Netlist namespace.
