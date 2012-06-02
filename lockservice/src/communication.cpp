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
        //queryStruct.Flag = 0;

        if (request.isTestFrame()) {             
            ss << "Test frame ontvangen van IP-nummer[" << queryStruct.sourceAddress << "], Poortnummer[" << queryStruct.sourcePort << "], Slotnummer["<< queryStruct.KeyIdentifier << "] ";
            Logger::info(ss.str());
            sendTestResponse();
            return false;
        } else {
            ss << "Request ontvangen van IP-nummer[" << queryStruct.sourceAddress << "], Poortnummer[" << queryStruct.sourcePort << "], Slotnummer["<< queryStruct.KeyIdentifier << "] ";
            Logger::info(ss.str());
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
    
    ss << "Test response terug sturen naar IP-nummer[" << queryStruct.sourceAddress << "], Poortnummer[" << queryStruct.sourcePort << "], Slotnummer["<< queryStruct.KeyIdentifier << "] ";
    Logger::info(ss.str());
    
    client->sendTo(buffer, response.getFrameSize(), queryStruct.sourceAddress, queryStruct.sourcePort);
}

void Communication::sendResponse(ResponseAnswer flags) {

    HanResponse response;

    void *buffer;

    response.setKeyIdentifier(queryStruct.KeyIdentifier);
    response.setUserIdentifier(queryStruct.UserIdentifier);
    response.setAnswer(flags);

    buffer = response.getFrame();

    ss << "Response terug sturen naar IP-nummer[" << queryStruct.sourceAddress << "], Poortnummer[" << queryStruct.sourcePort << "], Slotnummer["<< queryStruct.KeyIdentifier << "], Flag[" << flags << "]";
    Logger::info(ss.str());
    
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







