//////////////////////////////////////////////////////////////////////////////
// Class          : Factory													//
// Module/App     :	ext		   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
//																			//
//																			//
// Changes:																	//
//																			//
//																			//	
//////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECFACTORY_H__817094F2_18FA_4BC7_B7AF_CF35D1802F8A__INCLUDED_)
#define AFX_SECFACTORY_H__817094F2_18FA_4BC7_B7AF_CF35D1802F8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>

#include "Ext/Extdll.h"
#include "Ext/Extdefs.h"

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif 

class CCustomObject;

// Do not MODIFY This file.


// This file is used by ATRADER to create the registered objects.
// Only the Factory.cpp should updated when you add a new template.
// To Create a new indicator, use the extmovingaverage.cpp and extcciobject.cpp sample 
// by firstly copying the classes
// and creating the new class names using search and replace.
// EACH indicator must be registered in the custom object factory. 
// Just add the creator to you Initialise method on the factory.

class EXT_API CustomObjectFactory  
{
public:
	typedef CCustomObject* (*CreateSecFunction)(ECustomType type);
	typedef std::map<ECustomType, CreateSecFunction> CUSTOM_OBJECT_MAP;
	typedef std::map<ECustomType, CreateSecFunction>::iterator CUSTOM_OBJECT_MAP_ITERATOR;
	
	static CustomObjectFactory* Instance();

	void RegisterObject(ECustomType type, CreateSecFunction secFun);
	CUSTOM_OBJECT_MAP& GetCustomObjectMap();

	static void Initialise();


private:
	CustomObjectFactory(){};
	CustomObjectFactory(const CustomObjectFactory&){};
	CUSTOM_OBJECT_MAP theCreatorFunctions;
	CustomObjectFactory& operator= (const CustomObjectFactory&){return *this; }
	static CustomObjectFactory* g_pFactory;
};

#endif // !defined(AFX_SECFACTORY_H__817094F2_18FA_4BC7_B7AF_CF35D1802F8A__INCLUDED_)
