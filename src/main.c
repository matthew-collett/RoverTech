// main.c
#include <xc.h>
#include "system.h"
#include "rgb_sensor.h"

void main(void) {
    SYSTEM_Initialize();
    RGB_SENSOR_Initialize();
    
    while (1) {
        RGBColours colours = RGB_SENSOR_ReadColours();
        if (colours.clear != 0) {
            // Normalize RGB values by the clear value
            float normRed = (float) colours.red / colours.clear;
            float normGreen = (float) colours.green / colours.clear;
            float normBlue = (float) colours.blue / colours.clear;
            
            // Assume normalized red is the highest
            float highestValue = normRed;
            char* highestColour = "Red";

            // Compare normalized green with the current highest
            if (normGreen > highestValue) {
                highestValue = normGreen;
                highestColour = "Green";
            }

            // Compare normalized blue with the current highest
            if (normBlue > highestValue) {
                highestValue = normBlue;
                highestColour = "Blue";
            }
        } 
    }
}



