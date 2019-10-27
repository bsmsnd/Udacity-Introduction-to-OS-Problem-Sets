//
//  server.h
//  problemset1
//
//  Created by 陈东 on 9/6/19.
//  Copyright © 2019 Charlie Chen. All rights reserved.
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int server(int portno);
void process(char *temp);

#endif /* server_h */
