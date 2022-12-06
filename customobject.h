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


#ifndef _EXTCUSTOMOBJECT_H_
#define _EXTCUSTOMOBJECT_H_

#include <vector>
#include <string>

class CElement;

#include "EXT/EXTDll.h"
#include "EXT/EXTDefs.h"


typedef std::vector<int> INTEGERLIST;
typedef std::vector<double> DOUBLELIST;


//------------------------------------------------
// All Custom Indicators should be derived from CCustomObject
// EACH indicator must be registered in the custom object factory. See the samples on how to register.

class EXT_API CCustomObject : public CObject
{
	DECLARE_SERIAL( CCustomObject );
public:
	
	// Empty constructor is required
	CCustomObject();
	CCustomObject(ECustomType type) ;
	
	// Copy constructor
	CCustomObject(const CCustomObject& another);
	CCustomObject& operator=(const CCustomObject& another);

public:

	// Virtual Destructor is required
	virtual ~CCustomObject();

	// This is the data displayed in the chart parameters
	virtual CString GetItemString() const;
	virtual CString GetTitleString() const;
	virtual CString GetShortTitleString() const;
	
	// Returns true if the date is the object is valid otherwise false
	virtual bool CheckExpirationDate(const CString strDate) const;

	// Called when the indicator is be initialised from ATRADER
	virtual void Initialise(double param1, double param2, double param3);

protected:
	void CopyObject(const CCustomObject& another);
	void Init(void);

public:
	
	// Override these functions to do your custom processing
	virtual void Calculate();
	virtual double CalculateLast();
	
	// Called when the time frame has been recalcuated and the series need to be recalculated in its entirety
	virtual void Recalculate(void);

	virtual void ClearData();
	
	// Called to update the series with data at end of bar
	virtual void AddData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);
	
	// Called to update the indicator based on a real time intra bar update
	virtual void UpdateData(const time_t& time, const double& fOpen, const double& fHigh, const double& fLow,  const double& fClose,  const int& fVolume);	


	virtual DOUBLELIST& GetDataList(void)
	{
		 return m_DataList;
	}
	
	virtual int GetDataListSize(void) const
	{
		 return m_DataList.size();
	}

	DOUBLELIST& GetValueList()
	{
		return m_ValueList;
	}
	
	virtual int GetValueListSize() const 
	{
		return m_ValueList.size();
	}

	double GetLastDataValue() const
	{
		return m_lastDataValue;
	}

	void SetLastDataValue(double fVal)
	{
		m_lastDataValue = fVal;
	}

	double GetLastCalcValue() const
	{
		return m_lastCalcValue;
	}

	// Returns the int position of where to start drawing this indicator. For example, for an ema it is the 
	// period. Since before the period is defined, it we dont draw anything.

	virtual int GetStartPos() const 
	{
		return 0;
	}


	// If this function returns true, 
	// then the indicator will get the paint bar colours by calling GetBarPaintType and GetBarCurrentPaintType.

	virtual bool CanBarPaint()
	{
		return false;
	}

	virtual bool GetBarPaintType(int BarPos, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour)
	{
		return false;
	}

	virtual bool GetCurrentBarPaintType(int BarPos, int& nLineStyleType, int& nLineStyleThickness, COLORREF& nBarColour)
	{
		return false;
	}

	// This is the all singing all dancing window DeviceContext. Dont attempt to render on this unless you are a programming expert...
	virtual bool CanPaint()
	{
		return false;
	}

	virtual bool Paint(CDC* pDC)
	{
		return false;
	}

	// These parameters are set from the ATRADER dialog

	double& GetParam1()
	{
		return m_fParam1;
	}
	
	
	double& GetParam2()
	{
		return m_fParam2;
	}
	
	double& GetParam3()
	{
		return m_fParam3;
	}
	

	double findHigh(DOUBLELIST& list, int curpos, int periods);
	double findLow(DOUBLELIST& list, int curpos, int periods);
	double dataAt(DOUBLELIST& list, int curpos, int aposback);

	// Set the Object as Updated When you have finished calculations
	
	bool IsUpdated(void)
	{
		return m_bFirstBarUpdated;
	}

	// Call this after you have calculated the bars and ready to render.

	void SetUpdated(void)
	{
		m_bFirstBarUpdated = true;
	}

	// Call this after you have calculated the last bar and ready to render.

	bool IsCalculateLastUpdated(void)
	{
		return m_bCalculateLastUpdated;
	}

	void SetCalculateLastUpdated(void)
	{
		m_bCalculateLastUpdated = true;
	}

public:		

	
	
private:
	ECustomType m_Type;
	double m_fParam1;
	double m_fParam2;
	double m_fParam3;
	int m_StartPos;

protected:
	bool m_bFirstBarUpdated;	
	bool m_bCalculateLastUpdated;

	// The last calulated real time indicator tick from the market
	double m_lastCalcValue;
	
	// The last real time time from the market
	double m_lastDataValue;
	
	// Calculated Data is stored in the Value List
	DOUBLELIST m_ValueList;
	// Input Data is stored in the Data List to Calculate the Series
	DOUBLELIST m_DataList;

};

#endif

