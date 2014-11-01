#include "ElevationSubsystem.h"
#include "../Robotmap.h"
#include "Encoder.h"
#include <math.h>
#include "../Commands/DriveElevationCmd.h"

#ifdef DONT_COMPILE

ElevationSubsystem::ElevationSubsystem() 
 : PIDSubsystem("ElevationSubsystem", 0.04, 0.001, 0.0)
 , _elevationMotor(MODULE_A, PWM_CHAN_ELEVATION_MOTOR)
 , _elevationEncoder(MODULE_A, DIO_CHAN_ELEVATION_ENC_A,
		 	 	 	 MODULE_A, DIO_CHAN_ELEVATION_ENC_B)
 , _limitSwitch(MODULE_B, DIO_ELEVATION_LIMITSWITCH)
 , _UP_BOUND(180.0f) // degrees !TBD
 , _DOWN_BOUND(-180.0f) // degrees !TBD
 , _ENCODER_TICKS_PER_REVOLUTION(360.0f) // ticks !TBD
 , _GEAR_RATIO(1)
 , _count(0)
 , _currentSetPoint(0)
 , _printElevationValues(true)
 , _sendElevationValues(false)
 , _sendLcdElevationValues(false)

{

		_elevationMotor.SetSafetyEnabled(false);
		
		while (_limitSwitch.Get() == 0)
		{
			_elevationMotor.Set(-0.25f);
		}
		_elevationMotor.Set(0.0f);
		_elevationEncoder.Reset();
		
		
		SetSetpointRange(_UP_BOUND, _DOWN_BOUND);
		//_elevationEncoder.SetDistancePerPulse( (360.0f / _ENCODER_TICKS_PER_REVOLUTION) / (360.0f * _ENCODER_WHEEL_CIRCUMFERENCE) / ( _LAZY_SUSAN_CIRCUMFERENCE * 360.0f ) );
		
		_elevationEncoder.SetDistancePerPulse(_ENCODER_TICKS_PER_REVOLUTION / 360.0f * _GEAR_RATIO);
		_elevationEncoder.Start();
		SetSetpoint(0);
		_dsLCD = DriverStationLCD::GetInstance();
	//	_smartdash = SmartDashboard::GetInstance();
	//	_smartdash->PutData(this);
	    Enable();

}
    
void ElevationSubsystem::InitDefaultCommand() 
{
	SetDefaultCommand(new DriveElevationCmd(CommandBase::oi->turretJoystick, Joystick::kYAxis));
	// Set the default command for a subsystem here.
}

void ElevationSubsystem::SetElevation(float new_elevation) 
{
	SetSetpoint(new_elevation);
	_currentSetPoint = new_elevation;
	displayDebuggingInfo(new_elevation);
	Enable();
	
}

float ElevationSubsystem::GetElevation() 
{
	return _elevationEncoder.GetDistance();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

double ElevationSubsystem::ReturnPIDInput() 
{
	return _elevationEncoder.GetDistance();
}

void ElevationSubsystem::UsePIDOutput(double output) 
{
	_elevationMotor.Set(output);
}


bool ElevationSubsystem::AtSetpoint()
{
	return (fabs(GetPosition() - GetSetpoint()) < 0.1);
}

void ElevationSubsystem::displayDebuggingInfo(float elevation)
{
	if (_printElevationValues)
	{
		printf("Elevation: %-5.2f Enc: %-5.2f\n", elevation, (float)_elevationEncoder.Get());
	}
	
	if (_sendElevationValues)
	{
		SmartDashboard::GetInstance()->PutDouble("Elevation", (double)elevation);
	}
	if (_sendLcdElevationValues)
	{
		_dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Elevation: %f", elevation);
		_dsLCD->UpdateLCD();
	}
}

#endif
