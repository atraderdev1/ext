//////////////////////////////////////////////////////////////////////////////
// Class          : CustomObjectFactory										//
// Module/App     :	ext		   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
//	This class is used by atrader to create the custom objects  			//
//																			//
//																			//
// Changes:																	//
//																			//
//																			//	
//																			//
//////////////////////////////////////////////////////////////////////////////

// This file is used by ATRADER to create the registered objects.
// Only the Factory.cpp should updated when you add a new template.
// To Create a new indicator, use the extmovingaverage.cpp and extcciobject.cpp 
// sample by firstly copying the classes
// and creating the new class names using search and replace.
// EACH indicator must be registered in the custom object factory. 
// Just add the creator to you Initialise method on the factory.


#include "stdafx.h"

#include <map>
#include <string>

#include "Ext/Constructible.h"
#include "Ext/Factory.h"
#include "Ext/CustomObject.h"
#include "Ext/ExtCCIObject.h"
#include "Ext/ExtMovingAverageObject.h"

CustomObjectFactory* CustomObjectFactory::g_pFactory =NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif 

// EACH indicator must be registered in the custom object factory. See the samples on how to register.

void CustomObjectFactory::Initialise()
{
	if (g_pFactory==NULL)
		g_pFactory = new CustomObjectFactory;

	// Add your registered objects here. Dont forget to create the sec helper as below.

	g_pFactory->RegisterObject(EExtMovingAverage, SecHelper<CExtMovingAverageObject>::Create);
	g_pFactory->RegisterObject(EExtCCI, SecHelper<CExtCCIObject>::Create);

}


CustomObjectFactory* CustomObjectFactory::Instance()
{
	return g_pFactory ;
}

void CustomObjectFactory::RegisterObject(ECustomType type, CreateSecFunction fun)
{
	theCreatorFunctions.insert(std::pair<ECustomType,CreateSecFunction>(type, fun));
}

CustomObjectFactory::CUSTOM_OBJECT_MAP& CustomObjectFactory::GetCustomObjectMap()
{
	return theCreatorFunctions;
}


