#include "gtest/gtest.h"
#include "HanRequest.h"

TEST(HanRequestTest, testGetNormalFrame) {
    HanRequest instance;
    int i, frameSize = 12;
    char expectedResult[] = {
        0b00000100, 0b11010010, // key identifier 1234
        0b00000000, 0b00000111, 0b00011101, 0b01011111, // user identifier 466271
        0b00000100, 0b11010010, // code 1234
        0b00000000, // flags
        0b00000000, //data
        0b10100111, 0b00011101, // checksum
    };

    instance.setKeyIdentifier(1234);
    instance.setUserIdentifier(466271);
    instance.setCode(1234);
    instance.setTestFrame(false);
    instance.setLockStatus(true);

    char *actualResult = (char *) instance.getFrame();

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *(actualResult + i)) << "Byte " << i + 1 << " was incorrect.";
    }
}

TEST(HanRequestTest, testGetTestFame) {
    HanRequest instance;
    int i, frameSize = 12;
    char expectedResult[] = {
        0b00000000, 0b00000000, // key identifier 1234
        0b00000000, 0b00000000, 0b00000000, 0b00000000, // user identifier 466271
        0b00000000, 0b00000000, // code 1234
        0b00000001, // flags
        0b00000000, //data
        0b11111111, 0b00000001, // checksum
    };

    instance.setTestFrame(true);

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *((char *) instance.getFrame() + i)) << "Byte " << i << " was incorrect.";
    }
}

TEST(HanRequestTest, testSetFrame) {
	HanRequest instance;

    char frame[] = {
        0b00000100, 0b11010010, // key identifier 1234
        0b00000000, 0b00000111, 0b00011101, 0b01011111, // user identifier 466271
        0b00000100, 0b11010010, // code 1234
        0b00000000, // flags
        0b00000000, //data
        0b10100111, 0b00011101, // checksum
    };

    instance.setFrame(frame);

    EXPECT_EQ(1234, instance.getKeyIdentifier());
    EXPECT_EQ(466271, instance.getUserIdentifier());
    EXPECT_EQ(1234, instance.getCode());
    ASSERT_TRUE(instance.isLocked());
    ASSERT_FALSE(instance.isTestFrame());
}
