//////////////////////////////////////////////////////////////////////////////
// Class          : EXT														//
// Module/App     :	ext   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//																			//
// Remarks:																	//
//																			//
//																			//
// Changes:																	//
//																			//
//																			//	
//																			//
//////////////////////////////////////////////////////////////////////////////
//  Function:
//  

#ifndef _EXT_DEFS_H_
#define _EXT_DEFS_H_


#ifdef EXT_EXPORTS
#define EXT_API __declspec(dllexport)
#else
#define EXT_API __declspec(dllimport)
#endif

// Add each custom item in your dll here.

typedef enum
{
	EExtMovingAverage =0,
	EExtCCI =1,

}ECustomType;


 typedef enum { 
	EExtSimple,
	EExtExponential,
	EExtDoubleSmoothedExponential,
}EExtAverageType;

 typedef enum {
	EExtLast = 0,
	EExtOpen,
	EExtHigh,
	EExtLow,
	EExtTypical,
}EExtPriceType;

extern int numOfTypesMA;
extern const char* strTypesMA[];


#define LOG_STRING_LENGTH 1024
#define LOG_TITLE_STRING_LENGTH 512

#endif