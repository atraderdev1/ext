//////////////////////////////////////////////////////////////////////////////
// Class          : EXT														//
// Module/App     :	ext		   		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
//  Function:																//
//																			//
//  This file provides routines used to initialise the DLL					//
//  DLL.																	//
//																			//
//  Any application that wishes to use the DLL must obtain a dynamic link	//
//  to it's library.  To do this call InitExchange.							//
//  This function will initialise the DLL and provide the dynamic link.		//
//																			//
//																			//
//  This DLL exports class to be used by Applications.						//
//																			//
//////////////////////////////////////////////////////////////////////////////

// Do not MODIFY This file.

#ifndef _EXT_DLL_H_
#define _EXT_DLL_H_


#ifdef EXT_EXPORTS
#define EXT_API __declspec(dllexport)
#else
#define EXT_API __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////////////////////////
// InitUT()
////////////////////////////////////////////////////////////////////////////////
// Applications using a DLL must, during their InitInstance function, call
// this function.
//
// The InitEXT function provides the calling application with a dynamic
// link to the DLL, ensures that all static data members have been
// initialized and creates any per instance data.
//

EXT_API void InitEXT();

////////////////////////////////////////////////////////////////////////////////
// ExitEXT
////////////////////////////////////////////////////////////////////////////////
// Applications using a DLL must, during their ExitInstance function, call
// this function.
//
// The ExitEXT function clears an per application instance data
// created during the call to InitEXT.

EXT_API void ExitEXT();


#endif