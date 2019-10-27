//
//  server.c
//  problemset1
//
//  Created by 陈东 on 9/6/19.
//  Copyright © 2019 Charlie Chen. All rights reserved.
//

#include "server.h"

void process(char *temp)
{
    char * name;
    name = strtok(temp,":");
    
    // Convert to upper case
    char *s = name;
    while (*s) {
        *s = toupper((char) *s);
        s++;
    }
}

int server(int portno){
    int sockfd, newsockfd;
    socklen_t clilen;
    char buff[255];
    struct sockaddr_in serv_addr, cli_addr;
    
    /* create socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    
    /* init socket structure */
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    serv_addr.sin_port = htons(portno);  // converts the unsigned short integer hostshort from host byte order to network byte order
    
    /* bind the host address using bind() call */
    if (bind(sockfd, (struct sockaddr* )&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }
    
    /* start listening for clients */
    printf("now listening on port %d...\n", portno);
    listen(sockfd, 5);  // int listen(int sockfd, int backlog); The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow
    clilen = sizeof(cli_addr);
    
    
    // accept actual connection from the client
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }
    
    printf("Connection established with %u\n", cli_addr.sin_addr.s_addr);
    
    /* If connection is established, start communicating */
    bzero(buff, sizeof(buff));
    long n = read(newsockfd, buff, 255);
    
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    
    process(buff);
    printf("Message received: %s\n", buff);
    
    /* write a response to the client */
    n = write(newsockfd, "Message Received", 17);
    if(n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    
    return 0;
}

int main()
{
    server(8888);
    
    return 0;
}

