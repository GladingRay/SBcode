
#include"../include/client_server.h"

pthread_t threads[2] = {0, 0};
pthread_mutex_t mut;

int main(int argc, char * argv[]){
    int name=0;
    pthread_mutex_init(&mut, NULL);
    init_server_socket();
    init_client_socket(argv[1]);
    pthread_create(&threads[0], NULL, thread_server, NULL);
    sleep(3);
    pthread_create(&threads[1], NULL, thread_client, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    return 0;
}