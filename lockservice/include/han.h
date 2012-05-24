/* 
 * File:   han.h
 * Author: tristan
 *
 * Created on May 20, 2012, 2:26 AM
 */

#ifndef HAN_H
#define	HAN_H

#include <stdint.h>

typedef struct
{  
    uint16_t keyIdentifier;
    uint32_t userIdentifier;
    uint16_t code;
} requestframe;

#endif	/* HAN_H */

