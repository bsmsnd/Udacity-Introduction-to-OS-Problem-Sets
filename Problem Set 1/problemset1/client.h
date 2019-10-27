//
//  client.h
//  problemset1
//
//  Created by 陈东 on 9/6/19.
//  Copyright © 2019 Charlie Chen. All rights reserved.
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>

int client(const char* servername, const int portno, const char* buffer);

#endif /* client_h */
