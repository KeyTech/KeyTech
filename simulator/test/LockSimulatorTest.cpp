#include "Mocks.h"

TEST(LockSimulatorTest, testSetOutput)  {
	ifstream stream("test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ((unsigned int)474296, ls.getUserIdentifier());
	EXPECT_EQ((unsigned int)1234, ls.getPincode());

}

TEST(LockSimulatorTest, testGetStudentId)  {
	ifstream stream("test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ((unsigned int)474296, ls.getUserIdentifier());
}

TEST(LockSimulatorTest, testGetPin)  {
	ifstream stream("test/open.txt");

	if (stream.is_open())	cout << "file opened" << endl;
	else					cout << "file not opened";

	LockSimulator ls(&stream);
	ls.detectEntry();

	EXPECT_EQ(ls.getPincode(), (unsigned int)1234);
}

TEST(LockSimulatorTest, testGetDoorState)  {
	LockSimulator ls;

	ls.setLockState(OPEN);
	EXPECT_TRUE(ls.getLockState());
}

TEST(LockSimulatorTest, testSetDoorState)  {
	LockSimulator ls;

	ls.setLockState(CLOSED);
	EXPECT_FALSE(ls.getLockState());
}

