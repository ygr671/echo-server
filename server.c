#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define LOG(x, ...) printf("[DEBUG] " x "\n", ##__VA_ARGS__);

#define ERRIF(x) \
  if (x) \
  {       \
    printf(#x " error\n"); \
    exit(EXIT_FAILURE); \
  }

#define ERRIFCLOSESOCKFD(x) \
    if (x) \
    {       \
        printf(#x " error\n"); \
        close(sockfd); \
        exit(EXIT_FAILURE); \
    }

#define ERRIFCLOSEALL(x) \
    if (x) \
    {       \
        printf(#x " error\n"); \
        close(sockfd); \
        close(acceptfd); \
        exit(EXIT_FAILURE); \
    }



int main(void)
{
    struct sockaddr_in sa;
    struct sockaddr_in sa_client;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(7777);
    sa.sin_addr.s_addr = INADDR_ANY;
    socklen_t sizeof_sa_client = sizeof(sa_client);
    char login_message[] = "Welcome user !\n";
    char disconnect_message[] = "Goodbye user !\n";
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERRIF(sockfd == -1);

    int bind_res = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    ERRIFCLOSESOCKFD(bind_res == -1);

    int listen_res = listen(sockfd, 3);
    ERRIFCLOSESOCKFD(listen_res == -1);

    int keep_alive_1 = 1;
    while (keep_alive_1 == 1)
    {
        char client_ip[INET_ADDRSTRLEN];

        
        int acceptfd = accept(sockfd, (struct sockaddr *)&sa_client, &sizeof_sa_client); 
        ERRIFCLOSESOCKFD(acceptfd == -1);
       
        inet_ntop(AF_INET, &sa_client.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("[SYSTEM] : Client %s connected.\n", client_ip);

        int send_result = send(acceptfd, login_message, strlen(login_message), 0);
        ERRIFCLOSEALL(send_result == -1);
        
        int keep_alive_2 = 1;
        while (keep_alive_2 == 1)
        {
            char recv_buffer[1024] = {0};
            char send_buffer[1024] = {0};

            strncpy(send_buffer, "[COMMAND] ", 11);

            int send_result_1 = send(acceptfd, send_buffer, strlen(send_buffer), 0);
            ERRIFCLOSEALL(send_result_1 == -1);
            
            memset(send_buffer, 0, sizeof(send_buffer));

            int recv_result = recv(acceptfd, recv_buffer, sizeof(recv_buffer), 0);
            ERRIFCLOSEALL(recv_result == -1);
            if (recv_result == 0)
            {
                keep_alive_2 = 0;
            }
            else if (strncmp(recv_buffer, "exit", 4) == 0)
            {
                send_result_1 = send(acceptfd, disconnect_message, strlen(disconnect_message), 0);
                ERRIFCLOSEALL(send_result_1 == -1);
                printf("[SYSTEM] : Client %s disconnected.\n", client_ip);
                keep_alive_2 = 0;
            }
            else if (strncmp(recv_buffer, "shutdown", 8) == 0)
            {
                send_result_1 = send(acceptfd, disconnect_message, strlen(disconnect_message), 0);
                ERRIFCLOSEALL(send_result_1 == -1);
                printf("[SYSTEM] : Client %s asked for a shutdown.\n", client_ip);
                keep_alive_1 = 0;
                keep_alive_2 = 0;
            }
            else
            {
                LOG("%s", recv_buffer);

                strncpy(send_buffer, "[SERVER] ", 11);
                send_result_1 = send(acceptfd, send_buffer, strlen(send_buffer), 0);
                ERRIFCLOSEALL(send_result_1 == -1);

                memset(send_buffer, 0, sizeof(send_buffer));

                strncpy(send_buffer, recv_buffer, recv_result);
            
                send_result_1 = send(acceptfd, send_buffer, strlen(send_buffer), 0);
                ERRIFCLOSEALL(send_result_1 == -1);
            }
        }
        close(acceptfd);
    }
    close(sockfd);
    

    exit(EXIT_SUCCESS);
}
