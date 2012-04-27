#include "gtest/gtest.h"
#include "HanResponse.h"
#include "Defines.h"

TEST(HanResponseTest, testGetNormalFrame) {
    HanResponse instance;
    int i, frameSize = 12;
    char expectedResult[] = {
        0b00000100, 0b11010010, // key identifier 1234
        0b00000000, 0b00000111, 0b00011101, 0b01011111, // user identifier 466271
        0b00000001, // flags
        0b00000000, 0b00000000, 0b00000000, // data
        0b01110101, 0b00011000, // checksum
    };

    instance.setKeyIdentifier(1234);
    instance.setUserIdentifier(466271);
    instance.setTestFrameAnswer(false);
    instance.setAnswer(PERMISSION_GRANTED);

    char *actualResult = (char *) instance.getFrame();

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *(actualResult + i)) << "Byte " << i << " was incorrect.";
    }
}

TEST(HanResponseTest, testGetTestFame) {
    HanResponse instance;
    int i, frameSize = 12;
    char expectedResult[] = {
        0b00000000, 0b00000000, // key identifier 1234
        0b00000000, 0b00000000, 0b00000000, 0b00000000, // user identifier 466271
        0b01000000, // flags
        0b00000000, 0b00000000, 0b00000000, // data
        0b11111111, 0b01000000, // checksum
    };

    instance.setTestFrameAnswer(true);

    char *actualResult = (char *) instance.getFrame();

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *(actualResult + i)) << "Byte " << i << " was incorrect.";
    }
}
