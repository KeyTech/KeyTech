/*
 * Mocks.h
 *
 *  Created on: May 7, 2012
 *      Author: hanna
 */

#ifndef MOCKS_H_
#define MOCKS_H_

#include "googletest/gmock/gmock.h"
#include "googletest/gtest/gtest.h"
#include "StateMachine.h"
#include "LockSimulator.h"
#include "Defines.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

/*--------- StateMachine mock ----------*/
class StateMachineMock : public StateMachine   {

public:
	StateMachineMock(int argc, char** argv):StateMachine(argc, argv){this->runStateMachine();}
	MOCK_METHOD0(runStateMachine, void());
	MOCK_METHOD0(init, bool());
};

/*--------- LockSimulator mock ----------*/
class LockSimulatorMock : public LockSimulator  {

public:
	MOCK_METHOD0(detectEntry, bool());
	MOCK_METHOD0(GetDoorState, bool());
	MOCK_METHOD0(getStudentId, uint32_t());
	MOCK_METHOD0(getPin, uint16_t());
	MOCK_METHOD1(setOutput, int(uint8_t flags));
	MOCK_METHOD1(SetDoorState, void(bool state));
};

#endif /* MOCKS_H_ */
