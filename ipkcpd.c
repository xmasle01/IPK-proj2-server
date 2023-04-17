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

void send_err(char* mode, int flags)
{
    if(!strcmp(mode, "tcp"))
    {
        send(comm_socket, bye, strlen(bye), flags);
        perror("UNEXPECTED HAPPEND:");
        shutdown(comm_socket, SHUT_RDWR);
        close(comm_socket);

    }else if(!strcmp(mode, "udp"))
    {
        const char* payload_data = "Could not parse the message!";
        //int message_length = SEND_BYTE_ARR + strlen(payload_data);

        sendbuffer[0] = OPCODE;
        sendbuffer[1] = STATUS_CODE_ERROR;
        sendbuffer[2] = strlen(payload_data);
        //strcpy(sendbuffer[3], payload_data);
        strcat(sendbuffer+3,payload_data);
        perror("preco som tu?");
        int bytes_tx = sendto(Socket, sendbuffer, strlen(sendbuffer), 0, addr, addr_size);
        //close(Socket);
        // skopírujeme payload data do správy
        //memcpy(&message[4], payload_data, strlen(payload_data));

        //sprintf(output, "OK:%d\n", result);
    }
}

bool valid_expr(char* expr)
{
    int brcnt = 0;
    for(int i = 0; i< strlen(expr); i++)
    {
        if(expr[i] == '(')
        {
            brcnt++;
        }
        else if(expr[i] == ')')
        {
            brcnt--;
        }
    }
    if(brcnt != 0)
    {
        return false;
    }


    return true;
}

int calculate (char* expr)
{
    if(!valid_expr(expr) )
    {
        send_err(mode, flags);
    }

    char op = expr[1]; // the operator is always the second character
    int operand1, operand2;
    char *rest;
    operand1 = strtol(expr + 3, &rest, 10); // convert the first operand to an integer
    if (*rest == '(') { // if there is a subexpression, evaluate it recursively
        int subresult = calculate(rest);
        switch (op) {
            case '+':
                operand1 += subresult;
                break;
            case '-':
                operand1 -= subresult;
                break;
            case '*':
                operand1 *= subresult;
                break;
            case '/':
                operand1 /= subresult;
                break;
        }
        rest++; // move past the closing parenthesis
    }
    while (*rest != '\0' && *rest != ')') { // loop over remaining operands
        rest++; // move past the space
        operand2 = strtol(rest, &rest, 10); // convert the operand to an integer
        switch (op) {
            case '+':
                operand1 += operand2;
                break;
            case '-':
                operand1 -= operand2;
                break;
            case '*':
                operand1 *= operand2;
                break;
            case '/':
                operand1 /= operand2;
                break;
        }
    }
    return operand1;
}


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

int create_socket(char* mode, int flags)
{
    if(!strcmp(mode, "tcp"))
    {
        int welcome_socket = socket(AF_INET, SOCK_STREAM, flags);
        if (welcome_socket <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }

        int enable = 1;
        setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR,&enable, sizeof(enable));

        return welcome_socket;

    }else if(!strcmp(mode, "udp"))
    {
        int server_socket = socket(AF_INET, SOCK_DGRAM, flags);
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