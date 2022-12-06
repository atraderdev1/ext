/////////////////////////////////////////////////////////////////////////////
// Class          : CExtMovingAverageObject									//
// Module/App     :	ext		   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
// A class demonstrating how to create a custom Cpp indicator object		//
//																			//
// Changes:																	//
//																			//
//																			//
//																			//	
//																			//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#include "Ext/Extdll.h"
#include "Ext/Extdefs.h"
#include "Ext/Customobject.h"
#include "Ext/extmovingaverageobject.h"
#include "Ext/Colours.h"


CExtMovingAverageObject::CExtMovingAverageObject()
	: CCustomObject(EExtMovingAverage) 
{
	Init();

}

CExtMovingAverageObject::CExtMovingAverageObject(ECustomType type)
	: CCustomObject(type)
{
	Init();
}


CExtMovingAverageObject::~CExtMovingAverageObject()
{
}

CExtMovingAverageObject :: CExtMovingAverageObject(const CExtMovingAverageObject& another)
	: CCustomObject(EExtMovingAverage)
{
	CopyObject(another);	
}

CExtMovingAverageObject& CExtMovingAverageObject :: operator=(const CExtMovingAverageObject& another)
{
	
	CopyObject(another);
	return *this;
}


void CExtMovingAverageObject :: Initialise(double param1, double param2, double param3)
{
	m_nPeriod = (int)param1;
	m_nPeriod2 = (int)param2;
	
}


CString CExtMovingAverageObject::GetItemString() const
{
	return CString("ExtMovingAverage2");
}


CString CExtMovingAverageObject::GetTitleString() const
{
	char str[LOG_TITLE_STRING_LENGTH];
	int x=m_nType;

	if (m_nType ==EExtDoubleSmoothedExponential)
		sprintf(str, "Moving Average (%s Period %d %d, Shift %d )", 
			strTypesMA[m_nType], m_nPeriod,m_nPeriod2, m_nShift);
	else
			sprintf(str, "Moving Average (%s Period %d, Shift %d )", 
			strTypesMA[m_nType], m_nPeriod, m_nShift);
	return CString(str);
}

CString CExtMovingAverageObject::GetShortTitleString() const
{
	char str[LOG_TITLE_STRING_LENGTH];
	int x=m_nType;
	if (m_nType ==EExtDoubleSmoothedExponential)
		sprintf(str, "MA (%s %d,%d)", strTypesMA[m_nType], m_nPeriod, m_nPeriod2);
	else
		sprintf(str, "MA (%s %d)", strTypesMA[m_nType], m_nPeriod);
	return CString(str);
}

IMPLEMENT_SERIAL( CExtMovingAverageObject,	CObject,	1 );



bool CExtMovingAverageObject :: GetBarPaintType(int barPosition, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour)
{
	nLineStyleType= 1;
	nLineStyleThickness= 1;

	if (barPosition>0 && barPosition<m_ValueList.size())
	{
		if (m_ValueList[barPosition]>m_ValueList[barPosition-1])
		{
			nBarColour = RGBLtGreen;
			nLineStyleThickness= 2;

		}
		else
		{
			nBarColour = RGBLtRed;
		}
		return true;
	}
	return false;
}

bool CExtMovingAverageObject :: GetCurrentBarPaintType(int barPosition, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour)
{
	nLineStyleType= 1;
	nLineStyleThickness= 1;

	if (m_ValueList.back() > GetLastCalcValue())
	{
		nBarColour = RGBLtGreen;
		nLineStyleThickness= 2;
	}
	else
	{
		nBarColour = RGBLtRed;
	}
	return true;
}


void CExtMovingAverageObject :: AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
	
	switch(m_nPriceType)
	{
		default:
		case EExtLast:
		{
			m_lastDataValue = fClose;
			break;
		}
	
		case EExtOpen:
		{
			m_lastDataValue =fOpen;
			break;
		}
		case EExtHigh:
		{
			m_lastDataValue = fHigh;
			break;
		}
		case EExtLow:
		{
			 m_lastDataValue = fLow;
			break;
		}
		case EExtTypical:
		{
			double v= fHigh + fClose + fLow;
			v=v/3;
			m_lastDataValue =  v;
			break;
		}
	}
	m_DataList.push_back(m_lastDataValue);
	
}

void CExtMovingAverageObject :: UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume)
{
	switch(m_nPriceType)
	{
		default:
		case EExtLast:
		{
			m_lastDataValue = fClose;
			break;
		}
	
		case EExtOpen:
		{
			m_lastDataValue =fOpen;
			break;
		}
		case EExtHigh:
		{
			m_lastDataValue = fHigh;
			break;
		}
		case EExtLow:
		{
			 m_lastDataValue =fLow;
			break;
		}
		case EExtTypical:
		{
			double v= fHigh + fClose + fLow;
			v=v/3;
			m_lastDataValue =  v;
			break;
		}
	}
}

void CExtMovingAverageObject :: Recalculate(void)
{
	m_bCalculated =false;
	m_DataList.clear();
	m_ValueList.clear();
	m_IntermediateList.clear();
	total =0;	
	total2 =0;
	pos=0;
	pos2=0;
	frontpos=0;
	frontpos2 =0;
	calcpos=0;
}

void CExtMovingAverageObject :: Calculate()
{
	switch((EExtAverageType)m_nType)
	{
		default:
		case EExtSimple:
		{	

			CalculateSimpleMA();
			break;

		}
		case EExtExponential:
		{	
				
			CalculateExponential();
			break;

		}
		case EExtDoubleSmoothedExponential:
		{	

			CalculateDoubleSmoothed();	
			break;

		}

		
	}

	if (m_bCalculated ==true)
	{
		SetUpdated();
		CExtMovingAverageObject::CalculateLast();
	}
}

double CExtMovingAverageObject :: CalculateLast()
{
	switch((EExtAverageType)m_nType)
	{
		default:
		case EExtSimple:
		{	

			m_lastCalcValue = 	CalculateLastSimpleMA();
			break;

		}
		case EExtExponential:
		{	
				
			m_lastCalcValue = 	CalculateLastExponential();
			break;

		}
		case EExtDoubleSmoothedExponential:
		{	

			m_lastCalcValue = 	CalculateLastDoubleSmoothed();	
			break;

		}
	}
	return m_lastCalcValue;

}


// Simple Moving Average
//---------------------------------------------------------------------------------------------------------------------------------

void CExtMovingAverageObject :: CalculateSimpleMA()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod)
		return;
	
	while ( pos < size)
	{
		double firstprice;
		double CurrentPrice= m_DataList[pos];
		total = total + CurrentPrice;
		if (pos == m_nPeriod-1)
		{
			bDataValid = true;
			frontpos=0;
		}				
		if (pos >= m_nPeriod)
		{
			firstprice = m_DataList[frontpos];
			total = total -firstprice;
			frontpos++;
		}
		if (bDataValid == true)
		{
			double ma = total/(double)m_nPeriod;
			m_ValueList.push_back(ma);
			m_bCalculated =true;
		}
		else
			m_ValueList.push_back(0); // Not yet right number of values so undefined
		
		pos++;
		
	}
}


double CExtMovingAverageObject :: CalculateLastSimpleMA()
{

	int size = m_DataList.size();
	if (size <= m_nPeriod)
		return 0;
	
	double total2 = total;
	double lastma, CurrentPrice;
	
	CurrentPrice= m_lastDataValue;
	total2 = total2 + CurrentPrice;

	
	if (pos >= m_nPeriod)
	{
		total2 = total2 -m_ValueList[frontpos];
	}

	
	if (bDataValid)
	{
		lastma = total2/(double)m_nPeriod;
	
		m_lastCalcValue = lastma;
	}
	
		
	return m_lastCalcValue;
}


// Exponetial Moving Average
//---------------------------------------------------------------------------------------------------------------------------------

void CExtMovingAverageObject :: CalculateExponential()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod)
		return;
	
	
	double weightingConstant=0;
	weightingConstant = 2/(1+(double)m_nPeriod);
	double ma,lastma, CurrentPrice;
	
	while (pos < size)
	{
		CurrentPrice= m_DataList[pos];
		total = total + CurrentPrice;
		
		if (pos==m_nPeriod-1)
		{
			bDataValid = true;
		}
	
		if (pos >= m_nPeriod)
		{
			total = total -m_DataList[frontpos];
			frontpos++;
		}
		
		if (pos <= m_nPeriod)
		{
			calcpos = pos;
			lastma = total/(double)m_nPeriod;
		}
		else
		{
			lastma = m_ValueList[calcpos];
			calcpos++;
		}

		if (pos>=m_nPeriod-1)
		{
			ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
		
		}					
		
		if (bDataValid == true)
		{
			m_ValueList.push_back(ma);
			m_bCalculated =true;
		}
		else
			m_ValueList.push_back(0); // Not yet right number of values so undefined
			
		pos++;
		
	}
	
}

double CExtMovingAverageObject :: CalculateLastExponential()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod)
		return 0;
	
	double total2 = total;
	double weightingConstant=0;
	weightingConstant = 2/(1+(double)m_nPeriod);
	double ma,lastma, CurrentPrice;
	
	CurrentPrice= m_lastDataValue;
	total2 = total2 + CurrentPrice;
	
	if (pos==m_nPeriod-1)
	{
		bDataValid = true;
	}


	
	if (pos >= m_nPeriod)
	{
		total2 = total2 -m_ValueList[frontpos];
	}

	
	if (pos <= m_nPeriod)
	{
		lastma = total2/(double)m_nPeriod;
	}
	else
	{
		lastma = m_ValueList[calcpos];
	}

	if (pos>=m_nPeriod-1)
	{
		ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
	
	}					
	
	return ma;
}


// Weighted Moving Average
//---------------------------------------------------------------------------------------------------------------------------------

void CExtMovingAverageObject :: CalculateWeighted()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod)
		return;
	
	theFrontIterator = m_DataList.begin();
	theIterator = m_DataList.begin();	
	int c=0;
	while (c!=pos)
	{
		c++;
		theIterator++;
	}
	c=0;
	while (c!=frontpos)
	{
		c++;
		theFrontIterator++;
	}
	
				
	total =0;
	double weights =0;
	double ma = 0;

	while (theIterator != m_DataList.end())
	{

	
		if (pos >= m_nPeriod)
		{
			theFrontIterator = theIterator;

			int c=0;
			while (c<m_nPeriod && theFrontIterator !=m_DataList.begin())
			{
				theFrontIterator--;
				frontpos--;
				c++;
			}
			c=0; total =0;
			for (int x=1; x<= m_nPeriod; x++)
			{
				total = total + (double)x*(*theFrontIterator);
				theFrontIterator ++;
				frontpos++;
				weights=weights+(double)x;
			}
			ma = total/weights;
			bDataValid = true;

		}
		if (bDataValid == true)
		{
			m_ValueList.push_back(ma);
			m_bCalculated =true;
		}
		else
			m_ValueList.push_back(0); // Not yet right number of values so undefined

		pos++;
		theIterator++;
	}
}

double CExtMovingAverageObject :: CalculateLastWeighted()
{
	return m_lastCalcValue;
}


// Smoothed Moving Average
//---------------------------------------------------------------------------------------------------------------------------------

void CExtMovingAverageObject :: CalculateSmoothed()
{
}

double CExtMovingAverageObject :: CalculateLastSmoothed()
{
	return m_lastCalcValue;
}


// DoubleSmoothed Moving Average
//---------------------------------------------------------------------------------------------------------------------------------


void CExtMovingAverageObject :: CalculateDoubleSmoothed()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod+m_nPeriod2)
		return;
	
	double weightingConstant=0;
	weightingConstant = 2/(1+(double)m_nPeriod);
	double ma,lastma, CurrentPrice;
	
	
	// calculate the first moving average
	while (pos < size)
	{
		CurrentPrice= m_DataList[pos];
		total = total + CurrentPrice;
		
		if (pos==m_nPeriod-1)
		{
			bDataValid = true;
		}
	
	
		
		if (pos >= m_nPeriod)
		{
			total = total -m_DataList[frontpos];
			frontpos++;
		}

		
		if (pos <= m_nPeriod)
		{
			calcpos = pos;
			lastma = total/(double)m_nPeriod;
		}
		else
		{
			lastma = m_DataList[calcpos];
			calcpos++;
		}

		if (pos>=m_nPeriod-1)
		{
			ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
		
		}					
		
		if (bDataValid == true)
			m_IntermediateList.push_back(ma);
		else
			m_IntermediateList.push_back(0); // Not yet right number of values so undefined
			
		pos++;
		
	}
	
	// now work out 2nd average
	weightingConstant = 2/(1+(double)m_nPeriod2);
	while (pos2 < size)
	{
		// if we are less than x period

		CurrentPrice= m_IntermediateList[pos2];
		
		
		if (pos2>=m_nPeriod-1)
			total2 = total2 + CurrentPrice;
		
		if (pos2==m_nPeriod+m_nPeriod2-2)
		{
			bDataValid2 = true;
		}
	
	
		
		if (pos2 >= m_nPeriod+m_nPeriod2-1)
		{
			total2 = total2 -m_IntermediateList[frontpos2];
			frontpos2++;
		}

		
		if (pos2 <= m_nPeriod+m_nPeriod2-1)
		{
			calcpos2 = pos2;
			lastma = CurrentPrice;
			lastma = total2/(double)m_nPeriod2;
		}
		else
		{
			lastma = m_IntermediateList[calcpos2];
			calcpos2++;
		}

		if (pos2>=m_nPeriod+m_nPeriod2-2)
		{
			ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
		
		}					
		
		if (bDataValid2 == true)
		{
			m_ValueList.push_back(ma);
			m_bCalculated =true;
		}
		else
			m_ValueList.push_back(0); // Not yet right number of values so undefined
			
		pos2++;
		
	}
	
}

double CExtMovingAverageObject :: CalculateLastDoubleSmoothed()
{
	int size = m_DataList.size();
	if (size <= m_nPeriod || size <= m_nPeriod2)
		return 0;
	
	double subtotal = total;
	double subtotal2 = total2;


	double weightingConstant=0;
	weightingConstant = 2/(1+(double)m_nPeriod);
	double ma,lastma, CurrentPrice;
	
	CurrentPrice= m_lastDataValue;
	subtotal = subtotal + CurrentPrice;
	
	// calculate first average
	
	if (pos >= m_nPeriod)
	{
		subtotal = subtotal - m_DataList[frontpos];
	}

	
	if (pos <= m_nPeriod)
	{
		lastma = subtotal/(double)m_nPeriod;
	}
	else
	{
		lastma = m_ValueList[calcpos];
	}

	if (pos>=m_nPeriod-1)
	{
		ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
	
	}					
	
	// calculate 2nd average
	weightingConstant = 2/(1+(double)m_nPeriod2);
	subtotal = subtotal + CurrentPrice;
	
	if (pos2 >= m_nPeriod2)
	{
		subtotal2 = subtotal2 -m_IntermediateList[frontpos2];
	}

	
	if (pos2 <= m_nPeriod2)
	{
		lastma = subtotal2/(double)m_nPeriod2;
	}
	else
	{
		lastma = m_IntermediateList[calcpos2];
	}

	if (pos2>=m_nPeriod2-1)
	{
		ma =(CurrentPrice*weightingConstant)+lastma*(1-weightingConstant);
	
	}					
	return ma;
}




void CExtMovingAverageObject :: CopyObject(const CExtMovingAverageObject& another)
{
	CCustomObject::CopyObject(another);

	m_nPeriod = another.m_nPeriod;
	m_nPeriod2 = another.m_nPeriod2;
	m_nShift = another.m_nShift;
	m_nPriceType = another.m_nPriceType;
	
}

void CExtMovingAverageObject :: Init(void)
{

	m_nType = 1;
	m_nPeriod = 34;
	m_nPeriod2 = 6;

	m_nShift = 0;
	m_nPriceType =0;

	total =0;
	total2 =0;
	pos=0;
	pos2=0;
	frontpos=0;
	frontpos2 =0;
	calcpos=0;
//	periods = (ceil(((double)m_nPeriod+1)/2));


}

void CExtMovingAverageObject :: GetDataValues(DOUBLELIST& List)
{
	List = m_DataList;
}

void CExtMovingAverageObject :: GetValues(DOUBLELIST& List)
{
	List = m_ValueList;
}

void CExtMovingAverageObject :: GetCurrentValues(double& CurrentMA)
{
	CurrentMA = m_lastCalcValue;
}

void CExtMovingAverageObject :: GetLastValues(double& LastMA)
{
	LastMA = m_ValueList.back();
}



