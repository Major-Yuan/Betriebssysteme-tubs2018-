/*
    Auagabe 9.1 - 9.7 von Jicheng Yuan und Zhengyang Li
*/
#include "client.h"
#include <sys/socket.h>
#include <arpa/inet.h>

pthread_t       reading_thread;
int             client_socket;
//Add your global variables here
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void connect_to_server()
/*
    Server connect
*/
{
    //write your code here
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    // IP address conversion
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1)
    {
        perror("socket");
        exit_client(-1);

    }

    //    int bind_result = bind(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    //    if(bind_result == -1)
    //    {
    //        perror("bind error");
    //    }

    // Server connect
    int connect_result = connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(connect_result ==-1)
    {
        perror("connect!");
        exit_client(-1);
    }
}

//-------------------------------------------------------------

void handshake()
/*
    handshake
*/
{

    //write your code here
    //test
    char msg[MAX_MESSAGE_LENGTH] = "Handshake: Hello, I'm the client";
    int sendmsg;
    if((sendmsg = send(client_socket, msg, strlen(msg), 0)) == -1)
    {
        perror("send fail");
    }
    else
    {
     send(client_socket, msg, strlen(msg), 0);
     recv(client_socket, msg, MAX_MESSAGE_LENGTH, 0);
     printf("msg is: %s\n", msg);
    }
    usleep(1000);
}

//-------------------------------------------------------------

void send_message()
/*
    message send
*/
{

    //write your code here
    char msg_from_user[MAX_USER_INPUT];
    while(1) {
        char* msg = prompt_user_input(msg_from_user, MAX_USER_INPUT);
        if(strcmp(msg, "\n") != 0)
        {
            set_request(msg);
        }
        else
        {
            get_request();
        }

    }
}

//-------------------------------------------------------------
void set_request(char* message)
{
    //write your code here
    //(void) message; //please remove this if you implement this function
    char message_add_s[strlen(message) + 2];
    char recvmsg[MAX_MESSAGE_LENGTH];
//    for(int j = 0; j < (int)strlen(message_add_s) -1 ; j++)
//    {
//        message_add_s[j] = 0;
//    }
    memset(message_add_s, 0, sizeof(message_add_s));
    strcpy(message_add_s, "s:");
    for(int j = 0; j < (int)strlen(message) -1; j++)
    {
        message_add_s[j + 2] = message[j];
    }
    pthread_mutex_lock(&mymutex);
    //error process
    if((send(client_socket, message_add_s, strlen(message_add_s), 0) == -1) ||
        (recv(client_socket, recvmsg, MAX_MESSAGE_LENGTH, 0) == -1))
    {
        exit_client(-1);
    }
    pthread_mutex_unlock(&mymutex);
    int not_r_nack = strcmp(recvmsg, "r:nack");
    int not_r_ack = strcmp(recvmsg, "r:ack");
    if(!not_r_nack) {
        fprintf(stderr, "error about r:nack :%s\n", recvmsg);
        prompt_error();
        exit_client(-1);
    } else if(not_r_ack) {
        fprintf(stderr, "error about r:ack :%s\n", recvmsg);
        exit_client(-1);
    }
}


//-------------------------------------------------------------

void get_request()
{
    //write your code here
    char* request = "g:";
    char recvmsg[MAX_MESSAGE_LENGTH];
    pthread_mutex_lock(&mymutex);
    //error process
    if((send(client_socket, request, strlen(request), 0) == -1) ||
        (recv(client_socket, recvmsg, MAX_MESSAGE_LENGTH, 0) == -1))
    {
        exit_client(-1);
    }
    pthread_mutex_unlock(&mymutex);
    print_reply(recvmsg);
}

//-------------------------------------------------------------

void* read_continously(void* unused)
{
    (void) unused; //Mark variable as used for the compiler :-)

    //write your code here
    while (1)
    {
        usleep(READING_INTERVAL);
        get_request();
    }

    //this method should not return so dont care about return value
//    return NULL;
}

//-------------------------------------------------------------

void start_reader_thread()
{
    int ret ,stacksize = 20480;
//    pthread_t thid;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);
//    if(ret != 0)
//    {
//        printf("Error pthread_attr_init()!");
//        exit(EXIT_FAILURE);
//    }

    ret = pthread_attr_setdetachstate(&attr, stacksize);
//    if(ret != 0)
//    {
//        printf("Error pthread_attr_setdetachstate()!");
//        exit(EXIT_FAILURE);
//    }
    ret = pthread_create(&reading_thread, &attr, read_continously, NULL);
    if(ret != 0)
    {
         printf("Error pthread_create()!");
         exit(EXIT_FAILURE);
     }
}
