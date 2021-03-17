#include"../include/client_server.h"

int socket_of_client = 0;
struct sockaddr_in server_sockaddr_;
char input_buf[BUFF_SIZE];


int init_client_socket(char * server_ip){
    socket_of_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_sockaddr_, 0, sizeof(server_sockaddr_));
    server_sockaddr_.sin_family = AF_INET;
    server_sockaddr_.sin_addr.s_addr = htonl(convert_sip_to_binary(server_ip));
    //server_sockaddr_.sin_addr.s_addr = htonl(convert_sip_to_binary("127.0.0.1"));
    server_sockaddr_.sin_port = htons(SERVER_PORT);
    printf("[init_client_socket]:%x:%x\n", server_sockaddr_.sin_addr.s_addr, server_sockaddr_.sin_port);
    printf("[init_client_socket]:finished.\n");
    return 0;
}

void * thread_client(){
    printf("[thread_client]:%x:%x\n", server_sockaddr_.sin_addr.s_addr, server_sockaddr_.sin_port);
    int flag = connect(socket_of_client, (struct sockaddr *)(&server_sockaddr_), sizeof(struct sockaddr));
    if(flag == -1){
        printf("[thread_client]:connect failed.\n");
        return NULL;
    }
    printf("[thread_client]:connect finished.\n");
    while(1){
        scanf("%s", input_buf);
        if(input_buf[0] == 'q')break;
        flag = send(socket_of_client, input_buf, strlen(input_buf), 0);
        if(flag == -1){
            printf("[thread_client]:send failed.\n");
            return NULL;
        }
        printf("[thread_client]:send finished.\n");
    }
    close(socket_of_client);
    return NULL;
}

uint32_t convert_sip_to_binary(char * s){
    uint32_t res = 0;
    uint32_t t_res = 0;
    int i = 0;
    do{
        if(s[i]=='.' || s[i]=='\0'){
            res = res << 8;
            res = res | t_res;
            t_res = 0;
        }
        else {
            t_res = t_res * 10;
            t_res = t_res + s[i] - 48;
        }
        if(s[i] == '\0')break;
        i++;
    }while(1);
    printf("[convert_sip_to_binary]:%s->%x\n", s, res);
    return res;
}
