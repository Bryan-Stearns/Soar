#include "ilobject.h"
#include <iostream>
#include <cassert>

using std::string;
using std::vector;
using std::cout; using std::endl;
using std::ostream;

extern void pause();
/******************************************************************************
* ILObject Class Function Definitions
*
*
******************************************************************************
*/

/*InputLinkObject::InputLinkObject(string inParent, string inName, vector<eElementType>& inTypes, string inValue)
		: m_parentId(inParent), m_attribName(inName), m_elementTypes(inTypes), m_startingValue(inValue)
{
	
}*/

InputLinkObject::InputLinkObject()
{
	m_value.i		= NULL;
	m_value.id	= NULL;
	m_value.s		= NULL;
	m_value.f		= NULL;
}

/* Destructor
 *
 */  //TODO find out why this doesn't work correctly.  seems so simple
InputLinkObject::~InputLinkObject()
{
	m_elementTypes.clear();
//	if(m_value.i	!= NULL) delete m_value.i;
//	if(m_value.id != NULL) delete m_value.id;
//	if(m_value.s	!= NULL) delete m_value.id;
//	if(m_value.f	!= NULL) delete m_value.id;
}

//TODO comment
ostream& InputLinkObject::printType(ostream& stream, eElementType type)
{
	switch(type)
	{
		case ELEMENT_FLOAT:
			stream << "float element";
			break;
		case ELEMENT_INT:
			stream << "int element";
			break;
		case ELEMENT_ID:
			stream << "identifier";
			break;
		case ELEMENT_STRING:
			stream << "string element";
			break;
		default:
			stream << "BAAAAD things have happened";
			assert(false);
			break;
	}

	return stream;
}

//TODO comment
ostream& InputLinkObject::printValue(ostream& stream)
{
/*	switch(m_curType)
	{
		case ELEMENT_STRING:
			stream << *m_value.s;
			break;
		case ELEMENT_FLOAT:
			stream << *m_value.f;
			break;
		case ELEMENT_ID:
			stream << *m_value.id;
			break;
		case ELEMENT_INT:
			stream << *m_value.i;
			break;
		default:
			stream << "Wow...how did this happen?" << endl;
			assert(false);
			break;
	}*/
	return stream;
}
//TODO comment
void InputLinkObject::print(ostream& stream)
{
	stream << "Printing an input link object..." << endl;
	stream << "\tParent: \t" << m_parentId << endl;
	stream << "\tAttribute: \t" << m_attribName << endl;
	for(typesIterator tItr = m_elementTypes.begin(); tItr != m_elementTypes.end(); ++tItr)
	{
		stream << "\tType: \t" << printType(stream, *tItr) << endl;
	}
	stream << "\tValue: \t" << printValue(stream) << endl;
}

//TODO comment
void InputLinkObject::setType(string& inValue)
{
	m_curType = stringToType(inValue);
}

//TODO comment
void InputLinkObject::setStartValue(string& inValue)
{
	//sanity checks
	assert(!m_elementTypes.empty());
	assert(m_value.i == NULL);
	assert(m_value.id == NULL);
	assert(m_value.f == NULL);
	assert(m_value.s == NULL);

	switch(m_elementTypes[0])
	{
		case ELEMENT_STRING:
			m_value.s = new string(inValue);
			break;
		case ELEMENT_INT:
			m_value.i = new int(atoi(inValue.c_str()));
			break;
		case ELEMENT_FLOAT:
			m_value.f = new double(atof(inValue.c_str()));
			break;
		case ELEMENT_ID:
			m_value.id = new string(inValue);
			break;
		default:
			assert(!"got unexpected enum type....");
			break;
	}
}

void InputLinkObject::setUpdateValue(std::string& inValue)
{
	switch(m_curType)
	{
		case ELEMENT_INT:
		case ELEMENT_FLOAT:
		case ELEMENT_STRING:
			m_updateValue = inValue;
			break;
		case ELEMENT_ID:
			//TODO think about the case where an wme points to one id, and later to another.
			//isn't this conceivable?  and in that case, the ID could need to be updated
			assert(!"ID type should never receive an update value");
			break;
		default:
			break;			
	}
}

void InputLinkObject::setUpdateFrequency(string& inValue)
{
	if(inValue == k_onChangeString)
		{}//FIXME TODO pick up here
}

//does a case-insensitive string comparison, mapping strings to enums
eElementType stringToType(string& source)
{
	if(!stricmp(source.c_str(), k_intString.c_str()))
		return ELEMENT_INT;
	else if(!stricmp(source.c_str(), k_stringString.c_str()))
		return ELEMENT_STRING;
	else if(!stricmp(source.c_str(), k_floatString.c_str()))
		return ELEMENT_FLOAT;
	else if(!stricmp(source.c_str(), k_idString.c_str()))
		return ELEMENT_ID;
	else
	{
		cout << "bad type found in 'stringToType' >" << source << "< found." << std::endl;
		pause();
		exit(-1);
	}
}