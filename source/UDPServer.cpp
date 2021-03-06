#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <time.h>
#define __STDC_FORMAT_MACROS
#include <cinttypes>
#include <errno.h>


#define PORT 80

inline static uint64_t GetTickCountMs()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
}
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

// Driver code 
int main(int argc, char *argv[]) { 
    int sockfd; 

    unsigned char *buffer; 
    struct sockaddr_in servaddr, cliaddr; 
    ulong length;
    char var[256];
    bool isSilent=false;

    if(argc==1) {
        errno=ENOBUFS;
        perror("Missing buffer size");
        exit ( EXIT_FAILURE);
    } else if(argc ==2 ) {
        if(sscanf(argv[1],"%ld",&length)!=1) {
            errno=EINVAL;
            perror("Buffer size not an integer");
            exit( EXIT_FAILURE );
        }
    } else if(argc == 3) {
        if(sscanf(argv[1],"%ld",&length)!=1) {
            sscanf(argv[1],"%s",var);
            if(!strcmp(var,"-s")) {
                isSilent=true;
            } else {
                errno=EINVAL;
                perror("Invalid option");
                exit(EXIT_FAILURE);
            }
            if(sscanf(argv[2],"%ld",&length)!=1) {     
                errno=EINVAL;   
                perror("Buffer size not an integer");
                exit( EXIT_FAILURE );
            }
        } else {
            sscanf(argv[2],"%s",var);
            if(!strcmp(var,"-s")) {
                isSilent=true;
            } else {
                errno=EINVAL;
                perror("Invalid option");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        errno=EINVAL;
        perror("Invalid argument numbers");
        exit(EXIT_FAILURE);
    }
    buffer = (unsigned char *)calloc(length,1);
        // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit( EXIT_FAILURE ); 
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 

    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 

    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    socklen_t len; 
    ssize_t n;

    std::uint64_t tick=GetTickCountMs();
    ulong transferred=0;

    while (true) {
        len = sizeof(cliaddr);  //len is value/resuslt 

        n = recvfrom(sockfd, (unsigned char *)buffer, length,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        if(!isSilent) {
            printf("Bytes received : %ld\n", n); 
            dumpBuffer(buffer,n);
        }
        transferred+=n;
        if(transferred >= 1000000)
            break;
        memset(buffer,0,length);

    }

    std::uint64_t tick1=GetTickCountMs();
    std::uint64_t t=(tick1-tick)/1000;
    std::printf( "Transferred %ld bytes in %" PRId64 " seconds\n", transferred,t);
    return 0; 
} 

