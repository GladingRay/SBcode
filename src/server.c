#include"../include/client_server.h"

int server_listen_socket = 0 , server_connect_socket = 0;

struct sockaddr_in server_sockaddr;
struct sockaddr_in client_sockaddr;

char buf[BUFF_SIZE];

int init_server_socket(){
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sockaddr.sin_port = htons(SERVER_PORT);

    server_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_listen_socket == -1){
        printf("[init_srever_socket]:create socket failed.\n");
        return -1;
    }
    int flag = bind(server_listen_socket, (struct sockaddr *)(&server_sockaddr), sizeof(server_sockaddr));
    if(flag == -1){
        printf("[init_server_socket]:bind failed.\n");
        return -1;
    }
    flag = listen(server_listen_socket, 10);
    if(flag == -1){
        printf("[init_server_socket]:listen failed.\n");
        return -1;
    }
    printf("[init_server_socket]:successfully listenning...\n");
    return 0;
}

void * thread_server(){
    socklen_t s_t = sizeof(client_sockaddr);
    while(1){
        server_connect_socket = accept(server_listen_socket, (struct sockaddr *)(&client_sockaddr), &s_t);
        if(server_connect_socket == -1){
            printf("[thread_server]:accept failed.\n");
            continue;
        }
        printf("[thread_server]:accept finished.\n");
        while(server_connect_socket != 0){
            int n = recv(server_connect_socket, buf, BUFF_SIZE-1, 0);
            if(n<0){
                printf("[thread_server]:recv failed.\n");
                close(server_connect_socket);
                memset(buf, 0, strlen(buf));
                break;
            }
            else if(n == 0){
                close(server_connect_socket);
                printf("[thread_server]:connect closeed.\n");
                memset(buf, 0, strlen(buf));
                break;
            }
            buf[n] = '\0';
            printf("[%d]:%s\n", n, buf);
            FILE * fp = NULL;
            fp = fopen("./b.txt", "w");
            fputs(buf, fp);
            fclose(fp);
            memset(buf, 0, strlen(buf));
        }
    }
    close(server_listen_socket);
    return NULL;
}
