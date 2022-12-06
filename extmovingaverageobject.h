//////////////////////////////////////////////////////////////////////////////
// Class          : ExtMovingAverageObject									//
// Filename       : ExtMovingAverageObject.h								//
// Module/App     :	ext		   									            //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
// A class demonstrating how to create a custom Cpp indicator object		//																			//
//																			//
//																			//
//////////////////////////////////////////////////////////////////////////////


#ifndef _EXTMOVINGAVERAGEOBJECT_H_
#define _EXTMOVINGAVERAGEOBJECT_H_

#include "Ext/ExtDefs.h"
#include "Ext/Customobject.h"
#include "Ext/Constructible.h"

class CExtMovingAverageObject;

// In order to register the object with the Factory, add this line before your class implementation, changing the type to be your
// next class identifies from exdefs.h

//namespace
//{
//	SecHelper<CExtMovingAverageObject> RegisterCExtMovingAverageObject(EExtMovingAverage);
//}


//------------------------------------------------

class EXT_API CExtMovingAverageObject : public CCustomObject
{
	DECLARE_SERIAL( CExtMovingAverageObject );
public:
	
	// Empty constructor is required
	CExtMovingAverageObject(void) ;
	CExtMovingAverageObject(ECustomType type) ;
	
	// Copy constructor
	CExtMovingAverageObject(const CExtMovingAverageObject& another);
	CExtMovingAverageObject& operator=(const CExtMovingAverageObject& another);
	void Initialise(double param1, double param2, double param3);
	
public:
	
	virtual ~CExtMovingAverageObject();

	virtual CString GetItemString() const;
	virtual CString GetTitleString() const;
	virtual CString GetShortTitleString() const;
	
	virtual void AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);
	virtual void UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);

	virtual void Calculate(void);
	virtual double CalculateLast(void);
	virtual void Recalculate(void);

	void GetDataValues(DOUBLELIST& List);
	void GetValues(DOUBLELIST& List);
	
	void GetLastValues(double& LastMA);
	void GetCurrentValues(double& CurrentMA);
	
	virtual int GetStartPos() const 
	{
		return m_nPeriod;
	}

	virtual bool GetBarPaintType(int BarPos, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour);

	virtual bool GetCurrentBarPaintType(int BarPos, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour);


public:
	virtual void CopyObject(const CExtMovingAverageObject& another);
	virtual void Init();

	int m_nType;
	int m_nPeriod;
	int m_nPeriod2;
	int m_nPeriodSmooth;
	int m_nShift;
	int m_nPriceType;


private:

	void CalculateSimpleMA();
	double CalculateLastSimpleMA();

	void CalculateExponential();
	double CalculateLastExponential();

	void CalculateWeighted();
	double CalculateLastWeighted();

	void CalculateSmoothed();
	double CalculateLastSmoothed();

	void CalculateDoubleSmoothed();
	double CalculateLastDoubleSmoothed();

	DOUBLELIST m_IntermediateList;

private:

	double total;
	double total2;
	
	// for first average
	int pos;
	int frontpos;
	int calcpos;
	
	// for second average
	int pos2;
	int frontpos2;
	int calcpos2;

	bool bDataValid;
	bool bDataValid2;

	DOUBLELIST::iterator theFrontIterator;
	DOUBLELIST::iterator theIterator;
	DOUBLELIST::iterator theCalcIterator;
	bool m_bCalculated;

};


#endif

