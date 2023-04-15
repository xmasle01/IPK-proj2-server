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

int create_socket(char* mode)
{
    if(!strcmp(mode, "tcp"))
    {
        int family = AF_INET;
        int type = SOCK_STREAM;
        int welcome_socket = socket(family, type, 0);
        if (welcome_socket <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }
        int enable = 1;
        setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR,
        &enable, sizeof(enable));
        return welcome_socket;

    }else if(!strcmp(mode, "udp"))
    {
        int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (server_socket <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }
        return server_socket;
    }
    
}

int bind(int port, int Socket)
{
    unsigned short server_port = port;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_number);

    struct sockaddr *address = (struct sockaddr *) &server_addr;
    int address_size = sizeof(server_addr);
    
    if (bind(Socket, &address, address_size) < 0)
    {
        perror("ERROR: bind");
        exit(EXIT_FAILURE);
    }

}

void listen()
{
    int max_waiting_connections = 1;
    if (listen(welcome_socket, max_waiting_connections) < 0)
    {
        perror("ERROR: listen");
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