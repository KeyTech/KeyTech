/* 
 * File:   main.c
 * Author: root
 *
 * Created on April 22, 2012, 2:15 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include "han.h"
#include "errorHandler.h"

void signalChild(int signal);
void processRequest(request_arch *han_request, struct sockaddr_in *client_Addr, int socket_fd, socklen_t sin_size);

/*
 * 
 */
int main(int argc, char *argv[]) {

    int socket_fd;
    struct sockaddr_in server_Addr, client_Addr, *t_addr;
    socklen_t sin_size = sizeof (client_Addr);
    request_arch han_request;
    int bytes_read, buffer_size;
    int yes = 1;
    struct ifreq ifreq;
    pid_t childpid;

    // Check run parameters
    if (argc < 2) {
        DieWithUserMessage("Missing arguments", "Missing Interface name or Port number");
        printf("\n\n<Interface name> <Port number>\n\n");
    }

    // Create the socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        DieWithSystemMessage("socket() failed");
    }

    // Reusing port number
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) < 0) { //reuse addres when "address already in use".
        DieWithSystemMessage("setsockopt() failed");
    }

    // Interface name -> IP number
    strcpy(ifreq.ifr_name, argv[1]);
    if (ioctl(socket_fd, SIOCGIFADDR, &ifreq) != 0) {
        DieWithSystemMessage("ioctl() failed");
    }

    // Construct the server address structure
    t_addr = (struct sockaddr_in *) &ifreq.ifr_addr;
    server_Addr.sin_family = t_addr->sin_family;
    server_Addr.sin_addr = t_addr->sin_addr;
    server_Addr.sin_port = htons(atoi(argv[2]));

    // Set the max buffer size 
    if (ioctl(socket_fd, SIOCGIFMTU, &ifreq) != 0) {
        DieWithSystemMessage("ioctl() failed");
    }
    buffer_size = (ifreq.ifr_mtu);

    // Set the binding of the server UDP socket 
    if (bind(socket_fd, (struct sockaddr *) &server_Addr, sizeof (server_Addr)) < 0) {
        DieWithSystemMessage("bind() failed");
    }

    // Sig Handler
    signal(SIGCHLD, signalChild);

    for (;;) {
        printf("Waiting for connection...\n\n");

        // Block until received message from a lock
        bytes_read = recvfrom(socket_fd, (void *) &han_request, sizeof (han_request), 0, (struct sockaddr *) &client_Addr, &sin_size);

        if (bytes_read > 0) {
            childpid = fork();

            if (childpid < 0) {
                DieWithSystemMessage("fork() failed");
            }

            if (childpid == 0) {            
                processRequest(&han_request, &client_Addr, socket_fd, sin_size);
                
                if (close(socket_fd) < 0) {
                    DieWithSystemMessage("close() failed");
                }
                exit(0);
            }
        }
    }

    if (close(socket_fd) < 0) {
        DieWithSystemMessage("close() failed");
    }

    return (EXIT_SUCCESS);
}

void processRequest(request_arch *han_request, struct sockaddr_in *client_Addr, int socket_fd, socklen_t sin_size) {

    response_arch han_response;

    printf("Processing received data... \n\n");

    switch (han_request->flags) {
        case 0b00000000:
            printf("Changing Lock Status\n\n");

            han_response.slotnummer = han_request->slotnummer;
            han_response.flags = PERMISSION_GRANTED;
            han_response.IDnummer = han_request->IDnummer;
            han_response.checksum = han_request->checksum;
            
            printf("Sending back to lock number %u with the IP-adress %u the status flag %u.\n\n", han_request->slotnummer, client_Addr->sin_addr.s_addr, han_response.flags);

            int len = sendto(socket_fd, (void *) &han_response, sizeof (han_response), 0, (struct sockaddr *) client_Addr, sin_size);

            break;
        case 0b00000001:
            printf("Test frame\n\n");

            break;
        case 0b00000010:
            printf("Incorrect Checksum\n\n");

            break;
        case 0b00000100:
            printf("Lock is open\n\n");

            break;
        default:
            printf("No valid flag\n\n");
    }

}

void signalChild(int signal) {

    while (waitpid(-1, 0, WNOHANG) > 0);

}