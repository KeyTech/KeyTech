/*
 * LockSimulatorTest.cpp
 *
 *  Created on: May 8, 2012
 *      Author: hanna
 */

#include "Mocks.h"

TEST(LockSimulatorTest, testSetOutput)  {
	ifstream stream("/home/hanna/KeyTech/simulator/test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ(ls.getStudentId(), (unsigned int)474296);
	EXPECT_EQ(ls.getPin(), (unsigned int)1234);

}

TEST(LockSimulatorTest, testGetStudentId)  {
	ifstream stream("/home/hanna/KeyTech/simulator/test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ(ls.getStudentId(), (unsigned int)474296);
}

TEST(LockSimulatorTest, testGetPin)  {
	ifstream stream("/home/hanna/KeyTech/simulator/test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ(ls.getPin(), (unsigned int)1234);
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

