//////////////////////////////////////////////////////////////////////////////
// Class          : ExtCExtCCIObject										//
// Filename       : ExtCExtCCIObject.h										//
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


#ifndef _EXTCCIOBJECT_H_
#define _EXTCCIOBJECT_H_

#include "EXT/EXTDll.h"

#include <vector>
#include "Ext/CustomObject.h"
#include "Ext/Constructible.h"
#include "Ext/ExtMovingAverageObject.h"



class CExtCCIObject;

// In order to register the object with the Factory, add this line before your class implementation, changing the type to be your
// next class identifies from exdefs.h

//------------------------------------------------

class EXT_API CExtCCIObject : public CCustomObject
{
	DECLARE_SERIAL( CExtCCIObject );
public:
	
	// Empty constructor is required
	CExtCCIObject() ;
	CExtCCIObject(ECustomType type) ;
	
	// Copy constructor
	CExtCCIObject(const CExtCCIObject& another);
	CExtCCIObject& operator=(const CExtCCIObject& another);
	
	void Initialise(double param1, double param2, double param3);

	CExtMovingAverageObject m_Typical;
	CExtMovingAverageObject m_Absolute;

public:

	virtual ~CExtCCIObject();

	virtual CString GetItemString() const;
	virtual CString GetTitleString() const;
	virtual CString GetShortTitleString() const;
protected:
	void CopyObject(const CExtCCIObject& another);
	void Init(void);

public:
	virtual void Calculate();
	virtual double CalculateLast();	
	virtual void Recalculate(void);

	virtual void AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);
	virtual void UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);	

	virtual int GetStartPos() const 
	{
		return m_Typical.m_nPeriod;
	}

		
protected:
	int pos;
	int curpos;
	int stocpos;
	int frontpos;

	

	bool bDataValid;
	bool bDataValid2;

	bool bInitial;
	double totallowestlow;
	double totalhighesthigh;
	
};

#endif

