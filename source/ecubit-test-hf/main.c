/*
	Simple example to open a maximum of 4 devices - write some data then read it back.
	Shows one method of using list devices also.
	Assumes the devices have a loopback connector on them and they also have a serial number

	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o simple main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "../libftd2xx/release/ftd2xx.h"

#define BUF_SIZE 0x10

#define MAX_DEVICES		5



static void dumpBuffer(unsigned char *buffer, int elements)
{
	int j;

	printf(" [");
	for (j = 0; j < elements; j++)
	{
		if (j > 0)
			printf(", ");
		printf("0x%02X", (unsigned int)buffer[j]);
	}
	printf("]\n");
}



int main()
{
	unsigned char * pcBufRead = NULL;
	char * 	pcBufLD[MAX_DEVICES + 1];
	char 	cBufLD[MAX_DEVICES][64];
	DWORD	dwRxSize = 0;
	DWORD  	dwBytesWritten=8192;
	DWORD   dwBytesRead;
	FT_STATUS	ftStatus;
	FT_HANDLE	ftHandle[MAX_DEVICES];
	int	iNumDevs = 0;
	int	i;
	int	iDevicesOpen = 0;	
    int queueChecks = 0;
    long int timeout = 60; // seconds
    struct timeval  startTime;
	
	for(i = 0; i < MAX_DEVICES; i++) {
		pcBufLD[i] = cBufLD[i];
	}
	pcBufLD[MAX_DEVICES] = NULL;
	
	ftStatus = FT_ListDevices(pcBufLD, &iNumDevs, FT_LIST_ALL | FT_OPEN_BY_SERIAL_NUMBER);
	
	if(ftStatus != FT_OK) {
		printf("Error: FT_ListDevices(%d)\n", (int)ftStatus);
		return 1;
	}

	for(i = 0; ( (i <MAX_DEVICES) && (i < iNumDevs) ); i++) {
		printf("Device %d Serial Number - %s\n", i, cBufLD[i]);
	}


	/* Setup */
	if((ftStatus = FT_OpenEx(cBufLD[0], FT_OPEN_BY_SERIAL_NUMBER, &ftHandle[0])) != FT_OK){
	/* 
            This can fail if the ftdi_sio driver is loaded
            use lsmod to check this and rmmod ftdi_sio to remove
            also rmmod usbserial
 	*/
          printf("Error FT_OpenEx(%d), device %d\n", (int)ftStatus, i);
          printf("Use lsmod to check if ftdi_sio (and usbserial) are present.\n");
          printf("If so, unload them using rmmod, as they conflict with ftd2xx.\n");
          return 1;
	}
	
	printf("Opened device %s\n", cBufLD[0]);

	iDevicesOpen++;

		/* Read */
   
	gettimeofday(&startTime, NULL);

	for (queueChecks = 0; 
			dwRxSize < dwBytesWritten; 
			queueChecks++)
	{
		// Periodically check for time-out 
		if (queueChecks % 128 == 0)
		{
			struct timeval now;
			struct timeval elapsed;
			
			gettimeofday(&now, NULL);
			timersub(&now, &startTime, &elapsed);

			if (elapsed.tv_sec > timeout)
			{
				// We've waited too long.  Give up.
				printf("\nTimed out after %ld seconds\n", elapsed.tv_sec);
				break;
			}

			// Display number of bytes D2XX has received
			printf("%s%d", 
					queueChecks == 0 ? "Number of bytes in D2XX receive-queue: " : ", ",
					(int)dwRxSize);
		}

		ftStatus = FT_GetQueueStatus(ftHandle[0], &dwRxSize);
		if (ftStatus != FT_OK)
		{
			printf("\nFT_GetQueueStatus failed (%d).\n",
			(int)ftStatus);
		}
	}

	printf("\nGot %d (of %d) bytes.\n", (int)dwRxSize, (int)dwBytesWritten);
        
	if(ftStatus == FT_OK) {
		pcBufRead = realloc(pcBufRead, dwRxSize);
		memset(pcBufRead, 0x00, dwRxSize);
		printf("Calling FT_Read with this read-buffer:\n");
		ftStatus = FT_Read(ftHandle[0], pcBufRead, dwRxSize, &dwBytesRead);
		if (ftStatus != FT_OK) {
		printf("Error FT_Read(%d)\n", (int)ftStatus);
		}
		if (dwBytesRead != dwRxSize) {
			printf("FT_Read only read %d (of %d) bytes\n",
	       (int)dwBytesRead,
	       (int)dwRxSize);
		}
		printf("FT_Read read %d bytes.  Read-buffer is now:\n",
		(int)dwBytesRead);
		dumpBuffer(pcBufRead, (int)dwBytesRead);
		printf("%s test passed.\n", cBufLD[0]);
	} else {
		printf("Error FT_GetQueueStatus(%d)\n", (int)ftStatus);	
	}

	iDevicesOpen = i;
	/* Cleanup */
	for(i = 0; i < iDevicesOpen; i++) {
		FT_Close(ftHandle[0]);
		printf("Closed device %s\n", cBufLD[0]);
	}

	if(pcBufRead)
		free(pcBufRead);
	return 0;
}
