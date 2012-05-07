/*
 * Mocks.h
 *
 *  Created on: May 7, 2012
 *      Author: hanna
 */

#ifndef MOCKS_H_
#define MOCKS_H_

#include "googletest/gmock/gmock.h"
#include "StateMachine.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

class StateMachineMock : public StateMachine   {

public:
	StateMachineMock(int argc, char** argv):StateMachine(argc, argv){}
	MOCK_METHOD0(runStateMachine, void());
	MOCK_METHOD0(init, bool());
};


#endif /* MOCKS_H_ */
