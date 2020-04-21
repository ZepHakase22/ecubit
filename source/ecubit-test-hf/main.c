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


#include "../../libftd2xx/release/ftd2xx.h"

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
	DWORD	dwRxSize =  63448;
	DWORD  	dwBytesWritten=8192;
	DWORD   dwBytesRead;
	FT_STATUS	ftStatus;
	FT_HANDLE	ftHandle[MAX_DEVICES];
	int	iNumDevs = 0;
	int	i;
	int	iDevicesOpen = 0;	
    struct timeval  startTime;
    WORD isOn = 1;
    DWORD prevDwRxSize = 0;
	DWORD totalBytes=0;
	WORD nReset = 0;
	
	for(i = 0; i < MAX_DEVICES; i++) {
		pcBufLD[i] = cBufLD[i];
	}
	
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
	for(;;) {
		do
		{
			if(!isOn) {
				FT_Close(ftHandle[0]);
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
				printf("%s %d\n", "****************************************"" Number of reset ", ++nReset);
			}

			for(register WORD i=0; i<1000; i++) {
				prevDwRxSize = dwRxSize;
				ftStatus = FT_GetQueueStatus(ftHandle[0], &dwRxSize);
				if (ftStatus != FT_OK) {
					printf("Error FT_GetQueueStatus(%d)\n", (int)ftStatus);
				}
				if(dwRxSize==0 || prevDwRxSize == dwRxSize) {
					isOn = 0;
				} else {
					isOn = 1;
					break;
				} 
			}
		} while(dwRxSize <  63448);


		if(ftStatus == FT_OK) {
			pcBufRead = realloc(pcBufRead, dwRxSize);
			memset(pcBufRead, 0x00, dwRxSize);
//			printf("Calling FT_Read with this read-buffer:\n");
			ftStatus = FT_Read(ftHandle[0], pcBufRead, dwRxSize, &dwBytesRead);
			if (ftStatus != FT_OK) {
				printf("Error FT_Read(%d)\n", (int)ftStatus);
			}
			if (dwBytesRead != dwRxSize) {
				printf("FT_Read only read %d (of %d) bytes\n",
					(int)dwBytesRead,
					(int)dwRxSize);
			}
//			printf("FT_Read read %d bytes: \n",(int)dwBytesRead);
			dumpBuffer(pcBufRead, (int)dwBytesRead);
			totalBytes+=dwBytesRead;
			printf("Total Bytes read %d \n", totalBytes);
			if(totalBytes>= 1000000)
				break;
		} else {
			printf("Error FT_GetQueueStatus(%d)\n", (int)ftStatus);	
		}
	}
	struct timeval now;
	struct timeval elapsed;
	timersub(&now, &startTime, &elapsed);
	printf("Time elapsed: %ld\n", elapsed.tv_sec);

	/* Cleanup */
	for(i = 0; i < iDevicesOpen; i++) {
		FT_Close(ftHandle[0]);
		printf("Closed device %s\n", cBufLD[0]);
	}

	if(pcBufRead)
		free(pcBufRead);
	return 0;
}
