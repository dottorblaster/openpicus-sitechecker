#include "WF_Events.h"

	
/****************************************************************************
  FUNCTIONS TO HANDLE THE WIFI EVENTS
****************************************************************************/
BOOL ScanCompleted = FALSE;
//	CONNECTION SUCCESSFUL
void OnConnectionSuccessful(UINT8 ev, UINT16 evinfo)
{  
	IOPut (p21,on);
	StackDebug("Event: Connection Successful\r\n"); 
}

//	CONNECTION FAILED
void OnConnectionFailed(UINT8 ev, UINT16 evinfo)
{
	
}

//	CONNECTION TEMPORARLY LOST
void OnConnectionTempLost(UINT8 ev, UINT16 evinfo)
{
	
}

//CONNECTION REESTABLISHED
void OnConnectionReestablished(UINT8 ev, UINT16 evinfo)
{
	StackDebug("Event: Connection Reestablished\r\n");
}

//	CONNECTION PERMANENTLY LOST
void OnConnectionPermLost(UINT8 ev, UINT16 evinfo)
{
	IOPut (p21,off);
	
}

//	SCAN RESULT
void OnScanResult(UINT8 ev, UINT16 evinfo)
{
	#if defined(STACK_USE_UART)
	char buf[8];
	StackDebug("Event: Scan Results Ready, ");
	sprintf(buf, "%d", evinfo);
	StackDebug(buf);
	StackDebug(" results\r\n");
	#endif
	ScanCompleted = TRUE;
}

