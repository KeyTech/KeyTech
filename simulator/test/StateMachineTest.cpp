/*
 * StateMachineTest.cpp
 *
 *  Created on: May 7, 2012
 *      Author: hanna
 */
#include "Mocks.h"

TEST(StateMachineTest, testStateMachineInit) {
	int argc = 4;
	char *argv[argc];
	argv[0] = (char*)"simulator"; argv[1] = (char*)"127.0.0.1"; argv[2] = (char*)"5000"; argv[3] = (char*)"10";

	StateMachine fsm(argc,argv);

	fsm.init();
	EXPECT_TRUE(fsm.init());
}

TEST (StateMachineTest, testRunStateMachine) {
	int argc = 4;
	char *argv[argc];
	argv[0] = (char*)"simulator"; argv[1] = (char*)"127.0.0.1"; argv[2] = (char*)"5000"; argv[3] = (char*)"10";

	ifstream stream("/home/hanna/KeyTech/simulator/test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	StateMachine sm(argc, argv, &stream);
	sm.runStateMachine();
}
