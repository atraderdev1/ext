//////////////////////////////////////////////////////////////////////////////
// Class          :	SecHelper												//
// Module/App     :	Trader   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
// Copyright      : ATRADER			                                        //
//																			//
//////////////////////////////////////////////////////////////////////////////
// Author         : ATRADER	                                                //
//////////////////////////////////////////////////////////////////////////////
// Remarks:																	//
//																			//
//																			//
// Changes:																	//
//																			//	
//																			//
//////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_SECCONSTRUCTIBLE_H__AE15FF4B_1555_48A8_8050_58E1DDE05CF7__INCLUDED_)
#define AFX_SECCONSTRUCTIBLE_H__AE15FF4B_1555_48A8_8050_58E1DDE05CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "Ext/Factory.h"

class CCustomObject;

// EACH indicator must be registered in the custom object factory. Just add the creator to you Initialise method on the factory.

// Do not MODIFY This file.

template <class T>
class SecHelper
{
public:
	SecHelper(ECustomType type);
	static CCustomObject* Create(ECustomType type);
};

template <class T>
CCustomObject* SecHelper<T>::Create(ECustomType type)
{
	return new T(type);
}

template <class T>
SecHelper<T>::SecHelper(ECustomType type)
{
	CustomObjectFactory::Instance()->RegisterObject(type, SecHelper<T>::Create);
}

#endif // !defined(AFX_SECCONSTRUCTIBLE_H__AE15FF4B_1555_48A8_8050_58E1DDE05CF7__INCLUDED_)
