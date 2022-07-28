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

#include <NeoPixelConnect.h>
#include <stdio.h>
#include <Arduino.h>

NeoPixelConnect p(23, 1, pio0, 0);

void setup()
{
    Serial.begin(115200);
    sleep_ms(100);
    Serial.print("Init ok, ch.v.: ");
    Serial.println(rp2040_chip_version());

    _gpio_init(LED_BUILTIN);
    gpio_set_dir(LED_BUILTIN, OUTPUT);
}


void loop(){
    // digitalWrite(LED_BUILTIN, 1);

    p.neoPixelFill(random(0, 100), random(0, 100), random(0, 100), true);
    sleep_ms(300);
    
    //timer.user_data = 25;
}

