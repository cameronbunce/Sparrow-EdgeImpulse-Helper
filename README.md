This is just the start, a complement to the Sparrow firmware I'm working on.

# Goal

To build a program as an example of a device ( ESP32 ) connected to a Sparrow that interfaces with sensors and runs inference on a higher-power processor.

# Framework

The Sparrow attached to the serial interface here will poll the ESP32 for what it knows and relay upstream

I'm starting with implementing two inbound messages, "poll" and "init" with the idea of using the Sparrow's note templates to match the data coming from the ESP32 by sensor attached. We'll build a bit more code to reduce the individual message cost.

We need to plan out what data we'll send and build a note prototype against the datatype definitions below:

```c
// C macro to convert a number to a string for use below
#define _tstring(x)     #x

// Hard-wired constants used to specify field types when creating note templates
#define TBOOL           true                // bool
#define TINT8           11                  // 1-byte signed integer
#define TINT16          12                  // 2-byte signed integer
#define TINT24          13                  // 3-byte signed integer
#define TINT32          14                  // 4-byte signed integer
#define TINT64          18                  // 8-byte signed integer (note-c support depends upon platform)
#define TUINT8          21                  // 1-byte unsigned integer (requires notecard firmware >= build 14444)
#define TUINT16         22                  // 2-byte unsigned integer (requires notecard firmware >= build 14444)
#define TUINT24         23                  // 3-byte unsigned integer (requires notecard firmware >= build 14444)
#define TUINT32         24                  // 4-byte unsigned integer (requires notecard firmware >= build 14444)
#define TFLOAT16        12.1                // 2-byte IEEE 754 floating point
#define TFLOAT32        14.1                // 4-byte IEEE 754 floating point (a.k.a. "float")
#define TFLOAT64        18.1                // 8-byte IEEE 754 floating point (a.k.a. "double")
#define TSTRING(N)      _tstring(N)         // UTF-8 text of N bytes maximum (fixed-length reserved buffer)
#define TSTRINGV        _tstring(0)         // variable-length string
```

So for a n-array of DS18B20 temperature sensors with inference response for each, and host information, we might arrive at something like this:

{[("rom": "TSTRING(18)"), ("temperature": "TFLOAT32"), ("inference": "TSTRINGV")}
{[("platform": "TSTRINGV"), ("battery": "TFLOAT32"), ("version": "TFLOAT16")]}

This would be the response to the "init" message

The response to "poll" would walk each sensor and pack a json object in the fashion above but with the data populated.

A small bit of message data per polling cycle could be saved by sending the sensor ROM identifiers and creating a template per sensor instead of per sensor type, but we'll see what we get with this.