#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>


#define MAXLINE 2048 
#define PORT 80

// Driver code 
int main() { 
    int sockfd; 

    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr; 

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

    while (true) {
        len = sizeof(cliaddr);  //len is value/resuslt 

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer); 
        
    }

    return 0; 
} 

