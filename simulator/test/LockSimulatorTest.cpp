/*
 * LockSimulatorTest.cpp
 *
 *  Created on: May 8, 2012
 *      Author: hanna
 */

#include "Mocks.h"

TEST(LockSimulatorTest, testSetOutput)  {
	LockSimulator ls;

	ls.SetDoorState(OPEN);

	ls.setOutput(PERMISSION_GRANTED);
	EXPECT_FALSE(ls.GetDoorState());

	EXPECT_TRUE(ls.setOutput(ERR_UNAUTHORISED));

}

TEST(LockSimulatorTest, testGetStudentId)  {
	LockSimulator ls;
	ls.detectEntry();

	EXPECT_EQ(ls.getStudentId(), (unsigned int)0);
}

TEST(LockSimulatorTest, testGetPin)  {
	LockSimulator ls;
	ls.detectEntry();

	EXPECT_EQ(ls.getPin(), (unsigned int)0);
}

TEST(LockSimulatorTest, testGetDoorState)  {
	LockSimulator ls;

	ls.SetDoorState(OPEN);
	EXPECT_TRUE(ls.GetDoorState());
}

TEST(LockSimulatorTest, testSetDoorState)  {
	LockSimulator ls;

	ls.SetDoorState(CLOSED);
	EXPECT_FALSE(ls.GetDoorState());
}

