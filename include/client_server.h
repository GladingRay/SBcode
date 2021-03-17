#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>
#define SERVER_PORT 8081
#define BUFF_SIZE   100

void * thread_server();

void * thread_client();

int init_server_socket();

int init_client_socket(char * server_ip);

uint32_t convert_sip_to_binary(char * s);