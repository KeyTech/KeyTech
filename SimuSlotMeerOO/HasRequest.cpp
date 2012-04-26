/* 
 * File:   HasRequest.cpp
 * Author: hanna
 * 
 * Created on April 23, 2012, 10:51 AM
 */

#include "HasRequest.h"

HasRequest::HasRequest() {
    bzero(&header, sizeof(header));
}

HasRequest::~HasRequest() {
    cout << "HasRequest has been destroyed." << endl;
}

void HasRequest::fillStruct(int id, short pincode, short locknr, char status)  {
    this->header.id = id;
    this->header.pincode = pincode;
    this->header.locknr = locknr;
    
    if (status == OPEN) 
        this->header.flags = 0b00000100;
    else if (status == CLOSED)       
        this->header.flags = 0b00000000;
    
    this->header.checksum = 0;
    this->header.data = 0;
}

void HasRequest::fillTestStruct()
{
    this->header.id = 474296;
    this->header.pincode = 1234;
    this->header.locknr = 25;    
    this->header.flags = 0b00000001;
    this->header.checksum = 0;
    this->header.data = 0;
}

int HasRequest::sendStruct(struct sockaddr_in *sad, int sd)
{
    socklen_t caddrlen = sizeof(struct sockaddr_in);
    int n;
    char ipaddress[15];
    
    printf("struct size: %lu\n", sizeof(header));
    printf("struct size requestpacket: %lu\n", sizeof(request_packet));
    printf("sd is %d\n", sd);
    printf("caddrlen is %d\n", caddrlen);
    printf("sad ip is %s\n", inet_ntop(AF_INET, &(sad->sin_addr), ipaddress, 15));
    printf("address family is %i\n", sad->sin_family);
    printf("portnumber is %d\n", ntohs(sad->sin_port));
    
    if((n = sendto(sd, (const void *)&header, sizeof(header), 0, (const struct sockaddr*)sad, caddrlen)) < 0)   {
         perror("Error while sending"); exit(1);						   }
    
    return RECEIVE;
}