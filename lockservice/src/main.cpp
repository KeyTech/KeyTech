/* 
 * File:   main.cpp
 * Author: torisuta
 *
 * Created on May 16, 2012, 12:34 PM
 */

#include <iostream>
#include "lockservice.h"

LockService *lockservice;

/*
 * 
 */
int main(int argc, char** argv) {
    
    if (argc < 2) {
        cerr << "\nMissing the arguments <Interface name> <Port number>\n\n" << endl;
        return EXIT_FAILURE;
    }
    
    cout << "Booting the service. \n" << endl;
    
    lockservice = new LockService(argc, argv);

    return 0;
}

