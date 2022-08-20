/*
 Copyright (c) 2020-2021 Alan Yorinks All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU AFFERO GENERAL PUBLIC LICENSE
 Version 3 as published by the Free Software Foundation; either
 or (at your option) any later version.
 This library is distributed in the hope that it will be useful,f
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU AFFERO GENERAL PUBLIC LICENSE
 along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NeoPixelConnect.h"
#include <stdio.h>
#include <Arduino.h>
#include <iostream>
#include "flicker.h"
#include "pico.h"
#include "hardware/rtc.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
#include <chrono>
#include <string>
#include <time.h>


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

NeoPixelConnect p(23, 1, pio0, 0);
using namespace std;

void loop1();
void setup(){
}


void loop(){
    //Serial.begin(115200);
    //sleep_ms(100);
    //Serial.print("Init ok, ch.v.: ");
    //Serial.println(rp2040_chip_version());

    multicore_launch_core1(loop1);

    // _gpio_init(LED_BUILTIN);
    // digitalWrite(LED_BUILTIN, 1);
    Flicker R;
    Flicker G;
    Flicker B;

    while(1)
    {
        R.update();
        G.update();
        B.update();
        
        p.neoPixelFill(R.getVal(), G.getVal(), B.getVal(), true);
        // Serial.println(currentDateTime().c_str());
        multicore_fifo_push_blocking(R.getVal());
        sleep_ms(20);
    }
    //timer.user_data = 25;
    
}

void loop1()
{
    Serial.begin(115200);
    gpio_set_dir(LED_BUILTIN, OUTPUT);

    while(1)
    {
        gpio_put(LED_BUILTIN, LOW);
        uint32_t val = multicore_fifo_pop_blocking();
        gpio_put(LED_BUILTIN, HIGH);
        Serial.print(F("Updated"));        
    }
}