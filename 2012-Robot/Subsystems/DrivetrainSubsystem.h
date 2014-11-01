#ifndef DRIVETRAIN_SUBSYSTEM_H
#define DRIVETRAIN_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrainSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar _leftMotor;
	Jaguar _rightMotor;
	RobotDrive _drive; // robot drive system
	Joystick* _leftStick;
	Joystick* _rightStick;
	Encoder _leftMotorEncoder;
	Encoder _rightMotorEncoder;
	float _speedReduction;
	bool _printMotorValues;
	bool _sendMotorValues;
	bool _sendLcdMotorValues;
	const float _inchesPerRev;
	DriverStationLCD* _dsLCD;

public:
	// constructor
	
	DriveTrainSubsystem(Joystick* left_stick, Joystick* right_stick);
	
	void InitDefaultCommand();
	
	void DriveWithJoysticks();

	void Drive(float number_of_degrees_to_turn); // -90 is left, 0 straight, 90 is right
	
	void Drive(float left_motor, float right_motor);
	
	void SetSpeedReduction(float reduction); // 0 means standstill no matter what, 1.0 means no reduction at all
	
	float GetSpeedReduction();
	
	void ResetLeftMotorEncoder();
	
	void ResetRightMotorEncoder();
	
	float GetLeftMotorEncoderDistance();
	
	float GetRightMotorEncoderDistance();
	
	
	
	
	
private:
	void displayDebuggingInfo(float left, float right);

};

#endif
