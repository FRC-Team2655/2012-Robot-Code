#include "DriveTrainSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoysticksCmd.h"



DriveTrainSubsystem::DriveTrainSubsystem(Joystick* left_stick, Joystick* right_stick) 
 : Subsystem("DriveTrainSubsystem") 
 , _leftMotor(MODULE_A, PWM_CHAN_DRIVE_LEFTMOTOR)
 , _rightMotor(MODULE_A, PWM_CHAN_DRIVE_RIGHTMOTOR)  // CHANGE IT BACK TO A!
 , _drive(_leftMotor, _rightMotor)
 , _leftStick(left_stick)
 , _rightStick(right_stick)
 , _leftMotorEncoder( MODULE_A, DIO_CHAN_LEFT_DRIVE_ENC_A, MODULE_A, DIO_CHAN_LEFT_DRIVE_ENC_B) // The compiler did not like the numbers in the names,
 , _rightMotorEncoder( MODULE_A, DIO_CHAN_RIGHT_DRIVE_ENC_A , MODULE_A, DIO_CHAN_RIGHT_DRIVE_ENC_B ) // They do not do anything yet, but they are ready to be defined.
 , _speedReduction(DEFAULT_MOTOR_SPEED_REDUCTION)
 , _printMotorValues(false)
 , _sendMotorValues(false)
 , _sendLcdMotorValues(false)
 , _inchesPerRev(9.25f)
// , _rightMotorEncoder( DIO_CHAN_LEFT_DRIVE_ENC_A, ,   )



{
	_drive.SetExpiration(10.0f);
	_drive.SetSafetyEnabled(true);
	_dsLCD = DriverStationLCD::GetInstance();
	_leftMotorEncoder.Start();
	_rightMotorEncoder.Start();
}
    

void DriveTrainSubsystem::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveWithJoysticksCmd());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveTrainSubsystem::DriveWithJoysticks()
{
	float left = -(_leftStick->GetAxis(Joystick::kYAxis) * _speedReduction);
	float right = -(_rightStick->GetAxis(Joystick::kYAxis) * _speedReduction);
	
	displayDebuggingInfo(left, right);
	
	_drive.TankDrive( left, right );
}

void DriveTrainSubsystem::Drive(float number_of_degrees_to_turn)
{

}

void DriveTrainSubsystem::Drive(float left_motor, float right_motor)
{
	float left = -(left_motor * _speedReduction);
	float right = -(right_motor * _speedReduction);
	
	displayDebuggingInfo(left, right);
	
	_drive.TankDrive(left,right);
}

void DriveTrainSubsystem::SetSpeedReduction(float reduction)
{
	_speedReduction = reduction;
}

float DriveTrainSubsystem::GetSpeedReduction()
{
	return _speedReduction;
}

void DriveTrainSubsystem::displayDebuggingInfo(float left, float right)
{
	if (_printMotorValues)
	{
		printf("LeftMotor: %-6.2f  RightMotor: %-6.2f\n", left, right);
	}
	
	if (_sendMotorValues)
	{
		SmartDashboard::GetInstance()->PutDouble("LeftMotor", (double)left);
		SmartDashboard::GetInstance()->PutDouble("RightMotor", (double)right);
	}
	if (_sendLcdMotorValues)
	{
		_dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "RMotor:%-4.2f LMotor:%-4.2f", left, right );
		_dsLCD->UpdateLCD();
	}
}


void DriveTrainSubsystem::ResetLeftMotorEncoder()
{
	_leftMotorEncoder.Reset();
}


void DriveTrainSubsystem::ResetRightMotorEncoder()
{
	_rightMotorEncoder.Reset();
}

float DriveTrainSubsystem::GetLeftMotorEncoderDistance()
{
	float value = _leftMotorEncoder.Get() * _inchesPerRev;
	return value;
}


float DriveTrainSubsystem::GetRightMotorEncoderDistance()
{
	float value = _rightMotorEncoder.Get() * _inchesPerRev;
	return -value;
}
