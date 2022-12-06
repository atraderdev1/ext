//////////////////////////////////////////////////////////////////////////////
// Class          : CCustomObject											//
// Filename       : CCustomObject.h											//
// Module/App     :	ext		   									            //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
//																			//
// Changes:																	//
//																			//
//																			//	
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Ext/ExtDefs.h"
#include "Ext/customobject.h"

IMPLEMENT_SERIAL( CCustomObject,	CObject,	1 );

CCustomObject::	CCustomObject()
{
	Init();
	
}

CCustomObject::	CCustomObject(ECustomType type)
{
	m_Type = type;
	Init();
}



CCustomObject::~CCustomObject()
{
}


void CCustomObject::Init()
{
	m_bFirstBarUpdated =false;
}



CString CCustomObject::GetItemString() const
{
	return CString("Custom");
}


CString CCustomObject::GetTitleString() const
{
	return CString();
}

CString CCustomObject::GetShortTitleString() const
{
	return CString();
}

CCustomObject :: CCustomObject(const CCustomObject& another)
{
	CopyObject(another);
}

CCustomObject& CCustomObject :: operator=(const CCustomObject& another)
{
	CopyObject(another);
	return *this;
}

void CCustomObject :: CopyObject(const CCustomObject& another)
{
}	

void CCustomObject :: Initialise(double param1, double param2, double param3)
{
	m_fParam1 = param1;
	m_fParam2 = param2;
	m_fParam3 = param3;
}

bool CCustomObject :: CheckExpirationDate(const CString strDate) const
{
	return true;
}

void CCustomObject::Calculate()
{
}
double CCustomObject::CalculateLast()
{
	return 0;
}
void CCustomObject::Recalculate(void)
{
}

void CCustomObject::ClearData()
{
}
void CCustomObject::AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
}

void CCustomObject::UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
}





double CCustomObject :: findHigh(DOUBLELIST& list, int curpos, int periods)
{
	double f=0;
	int x= curpos;		
	do
	{
		if (list[x] > f)
			f = list[x];
		x--;	
	}
	while (x>0 && x>curpos-periods);

	return f;
}

double CCustomObject :: findLow(DOUBLELIST& list, int curpos, int periods)
{
	double f=99999999.0F;
	int x=curpos;	
	do
	{
		if (list[x] < f)
			f = list[x];
		x--;	
	}
	while (x>0 && x>curpos-periods);

	return f;
}

double CCustomObject :: dataAt(DOUBLELIST& list, int curpos, int aposback)
{
	if (curpos -aposback <0)
	{
		curpos =0;
	}
	else 
		curpos = curpos-aposback;
	return list[curpos];
}

