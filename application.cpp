/*
 * application.cpp
 *
 *  Created on: Aug 17, 2017
 *      Author: travis
 */

#include "application.h"

#include "Helium.h"

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

USARTSerial * serial = &Serial1;

Helium helium(serial);

Channel channel(&helium);

uint8_t b = 2;

void report_status(int status, int result = 0)
{
    if (helium_status_OK == status)
    {
        if (result == 0)
        {
            Serial.println("Succeeded");
        }
        else
        {
            Serial.print("Failed - ");
            Serial.println(result);
        }
    }
    else
    {
        Serial.println("Failed");
    }
}

void setup(){
    Serial.println("Starting");

    // Begin communication with the Helium Atom
    // The baud rate differs per supported board
    // and is configured in Board.h
    helium.begin(helium_baud_b115200);

    // Connect the Atom to the Helium Network
    Serial.print("Connecting - ");
    int status = helium.connect();
    // Print status
    report_status(status);

    // Begin communicating with the channel. This should only need to
    // be done once.
    //
    // NOTE: Please ensure you've created a channel called "Helium
    // MQTT" called in the Helium Dashboard.
    int8_t result;
    Serial.print("Creating Channel - ");
    status = channel.begin("Helium MQTT", &result);
    // Print status and result
    report_status(status, result);
}

void loop(){

}
