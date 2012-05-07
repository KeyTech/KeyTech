/*
 * StateMachineTest.cpp
 *
 *  Created on: May 7, 2012
 *      Author: hanna
 */

#include "googletest/gtest/gtest.h"
#include "Mocks.h"
#include "Defines.h"

TEST(StateMachineTest, testStateMachine) {
	int argc = 4;
	char *argv[argc];
	argv[0] = (char*)"simulator"; argv[1] = (char*)"127.0.0.1"; argv[2] = (char*)"5000"; argv[3] = (char*)"10";
	StateMachineMock fsm(argc, argv);

	EXPECT_CALL(fsm, runStateMachine());
	EXPECT_CALL(fsm, init());

	fsm.runStateMachine();
}
