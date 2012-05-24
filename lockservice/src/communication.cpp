/* 
 * File:   communication.cpp
 * Author: torisuta
 * 
 * Created on May 16, 2012, 2:05 PM
 */

#include "communication.h"

Communication::Communication(string serverAddress, uint16_t serverPort) {

    client = new UDPSocket(serverAddress, serverPort);
}

Communication::~Communication() {

}

bool Communication::waitForRequest() {

    HanRequest request;

    try {
        //memset(&queryStruct, 0, sizeof (struct ComStruct));

        char buffer[request.getFrameSize()];

        client->recvFrom(buffer, sizeof (buffer), queryStruct.sourceAddress, queryStruct.sourcePort);
        
        request.setFrame(buffer);

        queryStruct.KeyIdentifier = request.getKeyIdentifier();
        queryStruct.UserIdentifier = request.getUserIdentifier();
        queryStruct.PinCode = request.getCode();
        queryStruct.Flag = 0;

        if (request.isTestFrame()) {
            cout <<  "Debug is test frame :" <<request.isTestFrame() << " \n"<< endl;
            sendTestResponse();
            return false;
        } else {
            cout << "No test frame" << endl;
            return true;
        }
    } catch (HanException& ex) {
        return false;
    }
}

void Communication::sendTestResponse() {

    HanResponse response;

    void *buffer;

    response.setKeyIdentifier(queryStruct.KeyIdentifier);
    response.setUserIdentifier(queryStruct.UserIdentifier);
    response.setTestFrameAnswer(true);

    buffer = response.getFrame();
    
    cout <<  "Debug testresponse sourceAdress :" << queryStruct.sourceAddress << "\n" << endl;
    cout <<  "Debug testresponse sourcePort :" << queryStruct.sourcePort << "\n"<< endl;

    client->sendTo(buffer, response.getFrameSize(), queryStruct.sourceAddress, queryStruct.sourcePort);
}

void Communication::sendResponse(ResponseAnswer flags) {

    HanResponse response;

    void *buffer;

    response.setKeyIdentifier(queryStruct.KeyIdentifier);
    response.setUserIdentifier(queryStruct.UserIdentifier);
    response.setAnswer(flags);

    buffer = response.getFrame();

    client->sendTo(buffer, response.getFrameSize(), queryStruct.sourceAddress, queryStruct.sourcePort);
}

uint16_t Communication::getKeyIdentifier() {
    return queryStruct.KeyIdentifier;
}

uint32_t Communication::getUserIdentifier() {
    return queryStruct.UserIdentifier;
}

uint16_t Communication::getPincode() {
    return queryStruct.PinCode;
}







