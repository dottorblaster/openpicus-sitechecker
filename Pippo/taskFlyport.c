#include "taskFlyport.h"
#include "grovelib.h"
#include "rgb.h"

int wcap(char* host, char* page, char* word, TCP_SOCKET sock){
			int i=0;
			//TCPClientClose(sock);
			//TCPRxFlush(sock);
			/*UARTWrite(1, "prova2");
			if (!TCPisConn(sock)){
			TCPClientClose(sock);
			vTaskDelay(20);
			sock = INVALID_SOCKET;*/
			
			UARTWrite(1, "prova");
			vTaskDelay(500);
			/*}
			
			while(!TCPisConn(sock) && i<5){
				vTaskDelay(100);
				i++;
				UARTWrite(1, "O");
			}*/
			
			if(TCPisConn(sock)){
				UARTWrite(1, "connected");
				char GET[500];
				sprintf(GET, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", page, host);
				UARTWrite(1,GET);
				TCPWrite(sock, GET, strlen(GET));
				vTaskDelay(500);
				
				char response[1999];
				int k=0;
				while(TCPRxLen(sock)>0 && k<1998){
					TCPRead(sock, &response[k], 1);
					k++;
				}
				response[k]='\0';
				UARTWrite(1, response);
				/*char delims[] = "DOCTYPE";*/
				char *result = NULL;
				result = strstr( response, "DOCTYPE" );
				/*char response2[1000];
				sprintf(response2, "%s", result);*/
				if (result!=NULL) {
					TCPRxFlush(sock);
						return 1;
						
					}
					else{
						TCPRxFlush(sock);
					return 0;
					}
	
			}
			return 0;

}

void FlyportTask()
{	
	vTaskDelay(100);
	UARTWrite(1,"Welcome to GROVE NEST example!\r\n");

	// GROVE board
	void *board = new(GroveNest);
	void *rgb = new(Rgb, 1);

	// GROVE devices	
	// Digital Input
	attachToBoard(board, rgb, DIG1);
	
	// conf rgb
	configure(rgb, 1, 0, 255, 0);
	set(rgb, ON);
	
	// Connection to Network
	#if defined (FLYPORT_WF)
	WFConnect(WF_DEFAULT);
	while (WFStatus != CONNECTED);
	#endif
	#if defined (FLYPORTETH)
	while(!MACLinked);
	#endif
	UARTWrite(1,"Flyport connected... hello world!\r\n");
	vTaskDelay(200);
	
	char msg[100];
	
	TCP_SOCKET sock = INVALID_SOCKET;
	sock = TCPClientOpen("www.openpicus.com", "80");
	while(1)
	{	
		// Check pressure of button
		
		/*configure(rgb, 2, 255, 0, 0);
		set(rgb, ON);
		vTaskDelay(100);
		configure(rgb, 2, 0, 255, 0);
		set(rgb, ON);
		vTaskDelay(100);
		set(rgb, OFF);
		vTaskDelay(100);
		configure(rgb, 2, 0, 0, 255);
		configure(rgb, 1, 0, 0, 255);
		set(rgb, ON);
		*/
		vTaskDelay(100);
		configure(rgb, 1, 0, 255, 0);
		set(rgb, ON);
		
		if(wcap("www.openpicus.com", "/site/products", "flyport", sock)==1)
	{configure(rgb, 1, 0, 0, 255);
		set(rgb, ON);
		vTaskDelay(100);
		}
		else{configure(rgb, 1, 255, 0, 0);
		set(rgb, ON);
		vTaskDelay(100);
		}
		TCPRxFlush(sock);
	}
}
