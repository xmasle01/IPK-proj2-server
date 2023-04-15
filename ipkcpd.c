/* 
 * Projekt 2: Server na komunikaciu s klientom pre VUT FIT predmet IPK
 * Autor: Juraj Nikola Mašlej, xmasle01@vubr.cz
 * 2022/2023
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

bool check_args(int argc, const char * argv[])
{
    if(argc == 7) // checking if arguments are correct
    {
        int cnt = 0;
        if(!strcmp(argv[1],"-h"))
        {
            cnt++;
        }

        if(!strcmp(argv[3],"-p"))
        {
            cnt++;
        }

        if(!strcmp(argv[5], "-m"))
        {
            cnt++;
        }
        
        if(cnt != 3)
        {
            fprintf(stderr,"usage: %s -h <hostname> -p <port> -m <mode> %d\n", argv[0],cnt);
            exit(EXIT_FAILURE);
        }
    }else{
        fprintf(stderr,"usage: %s -h <hostname> -p <port> -m <mode> \n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[])
{
    check_args(int argc, char * argv[]);
    char* host,* mode;
    int port;
    host = argv[2];
    port = atoi(argv[4]);
    mode = argv[6];

}