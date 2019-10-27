//
//  client.c
//  problemset1
//
//  Created by 陈东 on 9/6/19.
//  Copyright © 2019 Charlie Chen. All rights reserved.
//

#include "client.h"

int client(const char* servername, const int portno, const char* buffer){
    int sockfd;
    long n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    /* create a socket point*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    
    /* obtain the server from servername
     * - servername can be either a hostname or an IPv4 address in standard dot notation
     */
    server = gethostbyname(servername);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR host not found");
        exit(0);
    }
    
    /* construct serv_addr */
    bzero((char *) &serv_addr, sizeof(serv_addr));  // The `bzero()` function sets the first n bytes to zero
    serv_addr.sin_family = AF_INET;  // code of the address family, should always set to AF_INET
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    /* Now connect to server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(1);
    }
    
    /* write to server */
    n = write(sockfd, buffer, strlen(buffer));
    
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    
    /* print what was sent */
    printf("%s\n", buffer);
    return 0;
}

int main(){
    char s[255] = "Hello World!";
    client("localhost", 8888, s);
}
