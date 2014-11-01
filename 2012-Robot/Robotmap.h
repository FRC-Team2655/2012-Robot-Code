#ifndef ROBOTMAP_H
#define ROBOTMAP_H


/** 
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
#define MODULE_A 1
#define MODULE_B 2

// PWMs 1..10
#define PWM_CHAN_DRIVE_LEFTMOTOR 1 // Mod:A Jag:1 
#define PWM_CHAN_DRIVE_RIGHTMOTOR 2 // Mod:A Jag:2
#define PWM_CHAN_COLLECTOR_BRUSHES_MOTOR 6 // Mod:A Vic:1
#define PWM_CHAN_COLLECTOR_INFEED_MOTOR 7 // Mod:A Vic:2

// PWMs Module B
#define PWM_CHAN_AZIMUTH_MOTOR 3  // Mod:A Jag:3
#define PWM_CHAN_LAUNCHER_MOTOR 5 // Mod:A Jag:5
#define PWM_CHAN_BRIDGEARM_LATCH_SERVO 6

// Spikes
#define RELAY_CHAN_COLLECTOR_BALLFEED_MOTOR 1 // Mod:A Spike:1
#define RELAY_CHAN_BRIDGEARM 2 // Mod:A Spike:2 
#define RELAY_CHAN_RELAY_FIRE 4 // Mod:A Spike:3
#define RELAY_CHAN_GATE 3 //Mod:A Spike:4
#define RELAY_CHAN_COMPRESSOR 5 // Mod:A Spike:5

// DIO 1..8 Module A
#define DIO_CHAN_LEFT_DRIVE_ENC_A 1
#define DIO_CHAN_LEFT_DRIVE_ENC_B 2
#define DIO_CHAN_RIGHT_DRIVE_ENC_A 3
#define DIO_CHAN_RIGHT_DRIVE_ENC_B 4
#define DIO_CHAN_LAUNCHER_LIMITSWITCH 7


// DIO 1..8 Module B
#define DIO_BRIDGEARM_LIMITSWITCH 1
#define DIO_AZIMUTH_LIMITSWITCH 2
#define DIO_CHAN_AZIMUTH_ENC_A 3
#define DIO_CHAN_AZIMUTH_ENC_B 4
#define DIO_CHAN_PRESSURE_SWITCH 5
#define DIO_CHAN_LIGHTSENSOR_LOW 6
#define DIO_CHAN_LIGHTSENSOR_MID 7
#define DIO_CHAN_LIGHTSENSOR_HIGH 8

// ANALOG 1..8
#define ANALOG_CHAN_SONAR_INPUT_A 1
#define ANALOG_CHAN_SONAR_INPUT_B 2
#define ANALOG_CHAN_SONAR_INPUT_C 3


#define DEFAULT_MOTOR_SPEED_REDUCTION 1.0f

// IO
#define LEFT_DRIVE_JOYSTICK 1
#define RIGHT_DRIVE_JOYSTICK 2
#define TURRET_JOYSTICK 3
#define GAME_PAD_JOYSTICK 4
// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#endif
