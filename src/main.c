// main.c
#include <xc.h>
#include "system.h"
#include "rgb_sensor.h"

void main(void) {
    SYSTEM_Initialize();
    RGB_SENSOR_Initialize();
    
    while (1) {
        unsigned char deviceId = RGB_SENSOR_ReadDeviceId();
        int success = 0;
        if (deviceId == 0xab) {
            success = 1;
        }
        
        
        // Check if the clear value is not zero to avoid division by zero
//        if (colours.clear != 0) {
//            // Normalize RGB values by the clear value
//            float normRed = (float) colours.red;
//            float normGreen = (float) colours.green;
//            float normBlue = (float) colours.blue;
//            
//            // Assume normalized red is the highest
//            float highestValue = normRed;
//            char* highestColour = "Red";
//
//            // Compare normalized green with the current highest
//            if (normGreen > highestValue) {
//                highestValue = normGreen;
//                highestColour = "Green";
//            }
//
//            // Compare normalized blue with the current highest
//            if (normBlue > highestValue) {
//                highestValue = normBlue;
//                highestColour = "Blue";
//            }
//        } 
    }
}



