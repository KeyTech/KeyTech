#include "googletest/gtest/gtest.h"
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
        0b00000000, 0b00000000, // checksum
    };

    instance.setKeyIdentifier(1234);
    instance.setUserIdentifier(466271);
    instance.setCode(1234);
    instance.setTestFrame(false);

    char *actualResult = (char *) instance.getFrame();

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *(actualResult + i)) << "Byte " << i << " was incorrect.";
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
        0b00000000, 0b00000000, // checksum
    };

    instance.setTestFrame(true);

    for (i = 0; i < frameSize; i++) {
        EXPECT_EQ(*(expectedResult + i), *((char *) instance.getFrame() + i)) << "Byte " << i << " was incorrect.";
    }
}
