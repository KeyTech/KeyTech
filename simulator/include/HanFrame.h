#ifndef HANFRAME_H_
#define HANFRAME_H_

#include <stdint.h>

class HanFrame {
public:
	HanFrame();

	/**
     * @return Retrieve the frame, ready to be sent.
     */
    void *getFrame();

    /**
     *
     * @return returns the size of the frame.
     */
    int getFrameSize();

protected:
    enum frameDefinition {
        CHECKSUM = 10,
        FRAME_SIZE = 12,
    };

    uint8_t frame[FRAME_SIZE];

    uint16_t calculateChecksum();
};

#endif /* HANFRAME_H_ */
