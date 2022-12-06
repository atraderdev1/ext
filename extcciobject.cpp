//////////////////////////////////////////////////////////////////////////////
// Class          : ExtCExtCCIObject										//
// Filename       : ExtCExtCCIObject.cpp									//
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
#include "math.h"


#include "Ext/ExtDefs.h"
#include "Ext/CustomObject.h"
#include "Ext/ExtCCIObject.h"

CExtCCIObject::CExtCCIObject()
	: CCustomObject(EExtCCI)
{
	Init();
}

CExtCCIObject::CExtCCIObject(ECustomType type)
	: CCustomObject(type)
{
	Init();
}


CExtCCIObject::~CExtCCIObject()
{
}

CExtCCIObject :: CExtCCIObject(const CExtCCIObject& another)
	: CCustomObject(EExtCCI)
{
	CCustomObject::CopyObject(another);
}

CExtCCIObject& CExtCCIObject :: operator=(const CExtCCIObject& another)
{
	
	CCustomObject::CopyObject(another);
	return *this;
}


void CExtCCIObject :: Initialise(double param1, double param2, double param3)
{
	m_Typical.m_nPeriod = (int)param1;
	
}


CString CExtCCIObject::GetItemString() const
{
	return CString("ExtCCI");
}


CString CExtCCIObject::GetTitleString() const
{
	char str[LOG_TITLE_STRING_LENGTH];
	sprintf(str, "EXT CCI (Period %d)", 
		m_Typical.m_nPeriod);
	
	return CString(str);
}

CString CExtCCIObject::GetShortTitleString() const
{

	char str[LOG_TITLE_STRING_LENGTH];
	sprintf(str, "CCI (%d)", m_Typical.m_nPeriod);
	
	return CString(str);
}

//------------------------------------------------

IMPLEMENT_SERIAL( CExtCCIObject,	CObject,	1 );


void CExtCCIObject :: CopyObject(const CExtCCIObject& another)
{
	m_Typical.CopyObject(another.m_Typical);
}

void CExtCCIObject :: Init(void)
{
	m_Typical.m_nType = EExtSimple;
	m_Typical.m_nPeriod = 14;
	m_Typical.m_nPriceType = EExtTypical;

	Recalculate();


}


void CExtCCIObject :: AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
	m_Typical.AddData(time, fOpen, fHigh, fLow, fClose, fVolume);
}

void CExtCCIObject :: UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
	m_Typical.UpdateData(time, fOpen, fHigh, fLow, fClose, fVolume);
}


void CExtCCIObject:: Calculate()
{
	int size = m_Typical.GetDataListSize();
	if ( size < 2*m_Typical.m_nPeriod-1)
		return;
	
	// If required then just recalcuale the moving average for the very last datavalue
	// as it has change during the build of a bar
	
	m_Typical.Calculate();
	
	if(stocpos==0)
		stocpos = m_Typical.m_nPeriod;
	
	while (pos < size)
	{
		double dev=0;
		double cci;
		double lastAve= m_Typical.GetValueList()[pos];
		double typicalVal= m_Typical.GetDataList()[pos];
		
		if (pos >= 2*m_Typical.m_nPeriod-1)
		{
			int c=stocpos;
			
			while (c < stocpos+m_Typical.m_nPeriod)
			{
				typicalVal= m_Typical.GetDataList()[c];
				dev= dev +fabs(lastAve-typicalVal);
				c++;
			}
			
			stocpos++;
			dev = dev /m_Typical.m_nPeriod;
			
		}
		
		if (pos >= 2*m_Typical.m_nPeriod-1)
		{
			bDataValid = true;
		}
		
			
			
		if (bDataValid ==true)
		{
			typicalVal= m_Typical.GetDataList()[pos];
			lastAve = m_Typical.GetValueList()[pos];
			if (dev ==0)
				cci=0;
			else
				cci = (typicalVal - lastAve)/(0.015f*dev);
			m_ValueList.push_back(cci);
			
		}
		else
		{
			m_ValueList.push_back(0);
		}			
		pos++;
	}
	SetUpdated();	
	CalculateLast();

}

double CExtCCIObject:: CalculateLast()
{
	int size = m_Typical.GetDataListSize();
	if ( size < 2*m_Typical.m_nPeriod)
		return 0;
	
	// If required then just recalcuale the moving average for the very last datavalue
	// as it has change during the build of a bar
	
	
	double dev=0;
	double cci;
	double lastAve= m_Typical.CalculateLast();
	double typicalVal= m_Typical.GetLastDataValue();

	if(stocpos==0)
		stocpos = m_Typical.m_nPeriod;
	
	if (pos >= 2*m_Typical.m_nPeriod-1)
	{
		int c=stocpos+1;
		
		dev= dev +fabs(lastAve-typicalVal);
		
		while (c < stocpos+m_Typical.m_nPeriod && c<size)
		{
			typicalVal= m_Typical.GetDataList()[c];
			dev= dev +fabs(lastAve-typicalVal);
			c++;
		}
		
		dev = dev /m_Typical.m_nPeriod;
		
	}
	
	if (pos >= 2*m_Typical.m_nPeriod-1)
	{
		bDataValid = true;
	}
	
		
		
	if (bDataValid ==true)
	{
		typicalVal= m_Typical.GetLastDataValue();
		if (dev ==0)
			cci=0;
		else
			cci = (typicalVal - lastAve)/(0.015*dev);
		m_lastCalcValue = cci;
		
	}
	else
	{
		m_lastCalcValue = 0;
	}			
	
	return m_lastCalcValue;
}


void CExtCCIObject :: Recalculate()
{
	bDataValid = false;
	totalhighesthigh =0;
	totallowestlow =0;
	pos=0;
	stocpos =0;
	curpos = 0;
	frontpos=0;
	m_Typical.Recalculate();
	m_ValueList.clear();
}


