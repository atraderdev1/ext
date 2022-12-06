//////////////////////////////////////////////////////////////////////////////
// Class          : EXT	INIT												//
// Module/App     :	ext		  		                                        //
// Project        : Atrader                                                 //
//////////////////////////////////////////////////////////////////////////////
// Remarks:																	//
//																			//
//																			//
// Changes:																	//
//																			//	
//																			//
//////////////////////////////////////////////////////////////////////////////
//  Function:
//  
//************************************************************************

#include "stdafx.h"                 // standard MFC header
#include "afxdllx.h"    			// standard MFC Extension DLL routines
// #### NOTE change following include to name of your own header ####

#include "Ext/Extdll.h"				// our own external declarations
#include "Ext/Factory.h"
#include "Ext/ExtMovingAverageObject.h"		// Include your custom Objects here
#include "Ext/ExtCCIObject.h"				// our own external declarations


static 				AFX_EXTENSION_MODULE NEAR extensionDLL;
								// Internal structure used by extension DLLs
static HINSTANCE 	ghInst = NULL;		// Our Instance handle


//Flag used to prevent a second attempt to initialize/deinitialize static data.
static bool g_bStaticsInitialized = false;
static int nThreadCount=0;
static int nProcessCount=0;

//***********************************************************************
// Function to initialize any static data in your entire project. This
// is unfortunately required due to a bug in extension DLLs which causes
// static data to not be initialized
//
// This function must be called from both the application Init<DLL>
// function and the Notifier Initialize.  This is to ensure that all
// applications, including the Notifier, perform the same initialization
// and that statics are only initialize once.
//***********************************************************************

int InitStatics(bool bInitialize)
{
	int iResult = 1;
    
	if (bInitialize)
	{
		// create a new CDynLinkLibrary for this app
		new CDynLinkLibrary(extensionDLL);
		
		if (!g_bStaticsInitialized)
		{
			CustomObjectFactory::Initialise();
		}
		
	}
	else if (g_bStaticsInitialized)
	{
	}
	
	g_bStaticsInitialized = bInitialize;

	return iResult;     
}



extern "C" int APIENTRY 
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
				// Extension DLL one-time initialization 
			if (!AfxInitExtensionModule(extensionDLL, hInstance))
				return 0;
			nProcessCount++;
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			nThreadCount++;
			break;
		}
		case DLL_THREAD_DETACH:
		{
			nThreadCount--;
			break;
		}
		case DLL_PROCESS_DETACH:
		{

			// Extension DLL per-process termination
		      AfxTermExtensionModule(extensionDLL);

			nProcessCount--;
			if (nProcessCount ==0)
				InitStatics(false);
			break;
		}
    }
    return 1;   // ok
}


//***********************************************************************
// This function must be called by each App that wants to use this
// service 
// #### NOTE: THE NAME MUST BE UNIQUE FOR EACH SERVICE DDL ####
// #### USE THE TWO LETTER SERVICE ID AS A SUFFIX.
// #### EG. MANAGE MESSAGE IS InitMS().  MESSAGES IS InitMG().
//***********************************************************************
void EXT_API InitEXT()
{
	InitStatics(true);
	//obtains dynamic link for application instance 
	//and ensures that Statics are initialized.
}            

//***********************************************************************
// This function must be called by each App that wants to use this
// service during it's ExitInstance function.
// #### NOTE: USE THE SAME NAMING CONVENTION UT FOR Init<DLL>.
// #### EG. MESSAGE IS ExitMG().
//***********************************************************************
void EXT_API ExitEXT()
{
	
	// #### NOTE Add your own per App clean up here ####
	// Don't call InitStatics(false) as other applications
	// may still be running.  The notifier is the only
	// application that shall shutdown DLLs.
}  

//***********************************************************************
// This function is always called "Initialize" and is called once by
// the Notifier at Startup and once again at Shutdown
//***********************************************************************
extern "C" int CALLBACK  Initialize(bool bStartup)
{   
	return InitStatics(bStartup);
}


