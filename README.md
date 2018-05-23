Teensy 3.6/Torqeedo Throttle Documentation

For more information visit [Sam Seifert&#39;s blog](https://samseifert.blogspot.com/2016/03/hacking-torqueedo-outboard-motors.html).

# Parts

- Teensy 3.6
- Torqeedo Ultralight 403
- Torqeedo Remote Throttle
- Torqeedo Powersupply

## Overview

The goal was to mimic the AS5045 encoder for the Torqeedo remote throttle so we can control the motor speed with the Pixhawk software. To do this we spliced the data line between the throttles main board and the encoder. We used a Teensy 3.6 to mimic the encoder becuase its speed was able to match the AS5045.

## Throttle Communication

The wire layout for the throttle&#39;s board is as follows:

- White: Power (Don&#39;t need this wire)
- Grey: Digital In (Don&#39;t need this wire)
- Purple: Digital Out
- Blue: Clock
- Green: Chip Select
- Yellow: Ground

## Teensy 3.6

Make sure you do not apply more than 3.3V to any signal pin on the Teensy. The Teensy&#39;s pin layout is as follows:

- Digital Out wire to pin 23.
- Clock wire to pin 22.
- Chip Select wire to pin 21.
- Pin 20 is for serial communication with the Pixhawk software; more on this below. (THV = Throttle Value)
- Connect the yellow ground wire to one of the ground pins on the Teensy.

[Here](https://www.pjrc.com/teensy/pinout.html) is a photo of the Teensy&#39;s pin layout for visualization.

## Calibration

Once the wires are connected to the Teensy you are now ready for calibration. Upload [this](https://github.com/nickdossantos/GingerJudge2/blob/master/calibrate.ino) code to the Teensy. The Teensy&#39;s LED will blink depending on the value it is being sent. Power on the remote throttle. Make sure the motor is connected to the Torqeedo battery. To Calibrate press &quot;cal&quot; button for 10 seconds.

- 1 Blink per second: tiller forward (2000) is being sent
- 20 Blinks per second: neutral (1000) is being sent
- 2.5 Blinks per second: tiller backward (0) is being sent

When the display shows &quot;cal up&quot; make sure the LED is blinking 1BPS and press the &quot;cal&quot; button again to calibrate for forward.

When the display shows &quot;cal stp&quot; make sure the LED is blinking 20BPS and press the &quot;cal&quot; button again to calibrate for neutral.

When the display shows &quot;cal dtn&quot; make sure the LED is blinking 2.5BPS and press the &quot;cal&quot; button again to calibrate for reverse.

If a error 22 message appears power the throttle down by holding for 10 seconds then power the throttle on again to clear the error message. If you don&#39;t see an error message you can move to the next step.

## Moving the Motor

Upload [this](https://github.com/nickdossantos/GingerJudge2/blob/master/teensyGo.ino) code to the Teensy, re-attach the magnetic dead mans switch and let her rip. The motor is defult at half throttle(1500). To change the speed of the motor 1001-2000 is forward. The higher the value the faster the motor will spin. 1000 is neutral and 1-999 is reverse. You can quick reference these constants for reference.

const int FORWARD\_VAL = 1990;
const int NEUTRAL\_VAL = 1000;
const int HALF\_THROTTLE = 1499;
const int REVERSE = 500;

If you have any more questions or want to see a more in depth explanation check out [this](https://samseifert.blogspot.com/2016/03/hacking-torqueedo-outboard-motors.html) blog post.
