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

