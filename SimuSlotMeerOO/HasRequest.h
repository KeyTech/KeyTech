/* 
 * File:   HasRequest.h
 * Author: hanna
 *
 * Created on April 23, 2012, 10:51 AM
 */

#ifndef HASREQUEST_H
#define	HASREQUEST_H

#include "Defines.h"


class HasRequest {

public:
    HasRequest();
    ~HasRequest();
    void fillStruct(int id, short pincode, short locknr, char status);
    void fillTestStruct();
    int sendStruct(struct sockaddr_in *sad, int sd);
        
private:
    request_packet header;
};

#endif	/* HASREQUEST_H */

