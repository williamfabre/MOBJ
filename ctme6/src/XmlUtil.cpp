#include "XmlUtil.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace Netlist {

std::string xmlCharToString(xmlChar* xmls)
{
	string s;

	if (xmls) {
		s = (char*)xmls;
		// The string must be deallocated
		// by the caller.
		free(xmls);
	}

	return s;
}


bool xmlGetIntAttribute(xmlTextReaderPtr reader,
			const string& attribute,
			int& value)
{
	xmlChar* textValue;

	// Provides the value of the attribute with the specified qualified name.
		// reader:	the xmlTextReaderPtr used
		// name:	the qualified name of the attribute.
	// Returns a string containing the value of the specified
	// attribute, or NULL in case of error. The string must be deallocated
	// by the caller.
	textValue=xmlTextReaderGetAttribute(reader,(const xmlChar*)attribute.c_str());
	// PROBLEM. ERROR FALLBACK
	if (textValue == NULL) {
		const xmlChar* nodeName;

		// The local name of the node.
			// reader:	the xmlTextReaderPtr used
		// Returns the local name or NULL if not available, the string
		// will be deallocated with the reader.
		nodeName = xmlTextReaderConstLocalName(reader);
		cerr << "[ERROR] \"" << attribute;
		cerr << "\" attribute missing in <";
		cerr << (const char*)nodeName << "> tag (line:";

		// Provide the line number of the current parsing point.
			// reader:	the user data (XML reader context)
		// Returns an int or 0 if not available
		cerr << xmlTextReaderGetParserLineNumber(reader) << ").";
		cerr << endl;
		return false;
	}
	value = atoi( (char*)textValue );
	return true;
}

bool isEnd(xmlTextReaderPtr reader)
{
	return xmlTextReaderNodeType(reader)
		== XML_READER_TYPE_END_ELEMENT;
}



}   // Netlist namespace.
